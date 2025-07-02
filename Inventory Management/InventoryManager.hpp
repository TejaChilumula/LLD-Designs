#pragma once
#include <iostream>
#include "Item.hpp"
#include "Supplier.hpp"
#include "Warehouse.hpp"
#include "Order.hpp"
#include "Observer.hpp"
#include "PricingStrategy.hpp"
#include "Product.hpp"
#include "ProductType.hpp"
#include "ReplenishmentStrategy.hpp"

#include <unordered_map>
#include <vector>
#include <stdexcept>
#include <sstream>

class InventoryManager {

private:
    Warehouse& getWarehouse(const std::string& name) {
        auto it = _warehouses.find(name);
        if (it == _warehouses.end())
            throw std::runtime_error("Warehouse not found: " + name);
        return it->second;
    }

    void notifyLow(Item::Id id, const Warehouse& wh, int threshold = 10) {
        int qty = wh.getStock(id);
        if (qty > threshold) return;

        for (auto* obs : _observers)
            obs->onLowStock(_items.at(id), wh.name(), qty);

        // auto-replenish if strategy present
        ReplenishmentStrategy* rs = _items.at(id).getReplenishmentStrategy();
        if (rs && rs->shouldReplenish(qty)) {
            int reorder = rs->reorderAmount();
            std::cout << "[AUTO] Replenishing "
                      << _items.at(id).name() << " by " << reorder << '\n';
            createOrder(OrderType::Purchase, wh.name(), {{id, reorder}});
        }
    }

    std::unordered_map<Item::Id, Item> _items;
    std::unordered_map<Supplier::Id, Supplier> _suppliers;
    std::unordered_map<std::string, Warehouse> _warehouses;
    std::unordered_map<ProductType::Id, ProductType> _productTypes;
    std::unordered_map<Product::Id, Product> _products;

    std::vector<Order> _orders;

    std::vector<LowStockObserver*> _observers;
    PricingStrategy* _pricing;

public:
    explicit InventoryManager(PricingStrategy* pricingStrategy) : _pricing(pricingStrategy) {}

     // ── CRUD helpers ───────────────────────────────────────────────
    Item::Id addItem(const std::string& name, double price, Product::Id productId){
        Item it{name, price, productId};
        _items.insert({it.id(), it});  // ✅ safe insert
        return it.id();
    }

    Supplier::Id addSupplier(const std::string& name, const std::string& contact){
        Supplier s{name, contact};
         _suppliers.insert({s.id(), s});  // ✅ no default constructor needed
        return s.id();
    }

    void addWarehouse(const std::string& name){
        _warehouses.emplace(name, Warehouse(name)); // ✅ No default constructor needed
        //tries to create a Warehouse object using operator[]. If name doesn't already exist, operator[] first default-constructs a Warehouse.
    }
    
    // ── Orders (uses Strategy + auto-replenish) ────────────────────
    Order::Id createOrder(OrderType type, const std::string& warehouseName, 
                const std::vector<std::pair<Item::Id,int>>& req){
                     Warehouse& wh = getWarehouse(warehouseName);
                    std::vector<OrderLine> lines;

                    for(auto& [id, qty]: req){
                        if(type == OrderType::Sale){
                            if(!wh.removeStock(id, qty))
                                throw std::runtime_error("Not enough stock in" + warehouseName);
                            notifyLow(id, wh);

                        }else
                            wh.addStock(id,qty);

                    double priceEach = _pricing->compute(_items.at(id).price(), qty);
                    lines.push_back({id,qty,priceEach});
                }
                _orders.emplace_back(type,warehouseName, lines);
                return _orders.back().id();
            }
    // ── Observer & Strategy setters ────────────────────────────────
        void subscribe(LowStockObserver* obs){
            _observers.push_back(obs);
        }

        void setPricingStrategy(PricingStrategy* ps){
            _pricing = ps;
        }

    std::string snapshot() const{
        std::ostringstream os;

        for(const auto& [name, wh] : _warehouses){
            os<<"Warehouse: "<<name<<"\n";
            for(const auto& [id,qty] : wh.allStock()){
                os<<" "<<_items.at(id).name() <<" = "<<qty<<"\n";
            }
        }
        return os.str();
    }

     // ── Product / ProductType API ─────────────────────────────────
    ProductType::Id addProductType(const std::string& name) {
    ProductType type(name);
    _productTypes.insert({type.id(), type});
    return type.id();
}

    Product::Id addProduct(const Product& product) {
       _products.insert({product.id(), product});
        return product.id();
    }

    Item& getItem(Item::Id id) {
    return _items.at(id);
}

        
};          