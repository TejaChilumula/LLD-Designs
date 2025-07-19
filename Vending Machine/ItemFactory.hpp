#pragma once

#include "Item.hpp"
#include "ItemType.hpp"
#include <memory>
#include <stdexcept>
#include <unordered_map>

using namespace std;

class ItemFactory {
private:
    static unordered_map<int, tuple<std::string, double, ItemType>> itemConfig;

public:
    static Item createItem(int itemId){
        auto it = itemConfig.find(itemId);
        if(it == itemConfig.end()){
            throw invalid_argument("Invalid item ID");
        }

        const auto& [name, price, type] = it->second;
        return Item(itemId, name, price, type);
    }

    static void registerItem(int itemId, const string& name, double price, ItemType type){
        itemConfig[itemId] = make_tuple(name, price, type);
    }
};

inline std::unordered_map<int, std::tuple<std::string, double, ItemType>> ItemFactory::itemConfig = {
    {1, {"Coke", 25.0, ItemType::BEVERAGE}},
    {2, {"Pepsi", 25.0, ItemType::BEVERAGE}},
    {3, {"Chips", 20.0, ItemType::SNACK}},
    {4, {"Candy", 10.0, ItemType::CANDY}},
    {5, {"Water", 15.0, ItemType::WATER}}
};