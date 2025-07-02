#pragma once
#include<set>
#include <string>
#include <atomic>
#include<cstdint>
#include "Product.hpp"
#include "ReplenishmentStrategy.hpp"

class Item{
    public:
    using Id = std::uint64_t;
    ReplenishmentStrategy* _replenish_strategy = nullptr;

    


    Item(const std::string& name, double price, Product::Id productId) : _id(generateId()), _name(name), _price(price), _product_id(productId){}

    Id id() const {return _id;}

     // getters
    const std::string& name() const {return _name;}

    double price() const { return _price;}

    void setPrice(double price) { _price = price;}


    // Optional At Last
    void setReplenishmentStrategy(ReplenishmentStrategy* strategy) {
    _replenish_strategy = strategy;
    }

    ReplenishmentStrategy* getReplenishmentStrategy() const {
        return _replenish_strategy;
    }


    private:
        static Id generateId(){
            static std::atomic<Id> counter{1};
            return counter++;
        }
    Id _id;
    std:: string _name;
    double _price;
    Product::Id _product_id;
};