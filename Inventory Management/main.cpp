#include "InventoryManager.hpp"
#include "ProductType.hpp"
#include "ProductBuilder.hpp"
#include <iostream>
#include<set>

/*
✅ Patterns Successfully Used
Pattern	Where It's Working
Strategy	PricingStrategy and ReplenishmentStrategy
Observer	ConsoleObserver via LowStockObserver
Inventory Manager	Core controller to route orders, warehouse ops
Builder (bonus)	ProductBuilder for clean product creation
*/

class ConsoleObserver : public LowStockObserver {
public:
    void onLowStock(const Item& item, const std::string& warehouse, int qty) override {
        std::cout << "[ALERT] Low stock: " << item.name()
                  << " in " << warehouse << " (qty: " << qty << ")\n";
    }
};

int main() {
    BulkPricing pricing;
    InventoryManager manager(&pricing);


    ConsoleObserver alert;
    manager.subscribe(&alert);

    manager.addWarehouse("W1");

    ProductType::Id clothesTypeId = manager.addProductType("Clothes");

    // Create products using builder
    ProductBuilder builder;
    Product penProduct = builder.setName("Pen")
                                 .setDescription("Blue ink pen")
                                 .setType(clothesTypeId)
                                 .build();

    Product clipProduct = builder.setName("Clip")
                                  .setDescription("Paper clip")
                                  .setType(clothesTypeId)
                                  .build();

    // Add products to inventory
    Product::Id penPid = manager.addProduct(penProduct);
    Product::Id clipPid = manager.addProduct(clipProduct);

    // Add items (SKUs) linked to products - Stock Keeping Unit - unique Identifier - Ex: Tshirt - Black - Size --- SKU = TS-BLK-M
    Item::Id pen = manager.addItem("Pen", 1.0, penPid);
    Item::Id clip = manager.addItem("Clip", 0.1, clipPid);


    // At Last --- Optional
    FixedThresholdReplenishment penReplenish(20, 100);
    FixedThresholdReplenishment clipReplenish(10, 50);

    manager.getItem(pen).setReplenishmentStrategy(&penReplenish);
    manager.getItem(clip).setReplenishmentStrategy(&clipReplenish);
    ////////////////////////////////////////////////

    manager.createOrder(OrderType::Purchase, "W1", {{pen, 200}, {clip, 50}});
    manager.createOrder(OrderType::Sale, "W1", {{clip, 45}}); // triggers alert

    // Show snapshot
    std::cout << "\n--- Inventory Snapshot ---\n";
    std::cout << manager.snapshot();



    
}
