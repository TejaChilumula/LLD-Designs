#pragma once

#include <unordered_map>
#include <vector>
#include <stdexcept>
#include "ItemShelf.hpp"

class Inventory {

private:
    unordered_map<int, ItemShelf> shelves;

public:

    void addShelf(const ItemShelf& shelf){
        shelves[shelf.getShelfId()] = shelf;
    }

    bool isAvailable(int shelfId) const {
        auto it = shelves.find(shelfId);
        return it != shelves.end() && !it->second.isEmpty();
    }

    const Item& getItem(int shelfId) const {
        if(!isAvailable(shelfId)){
            throw runtime_error("Item not available");
        }
        return shelves.at(shelfId).getItem();
    }

    void dispenseItem(int shelfId){
        if(!isAvailable(shelfId)){
            throw runtime_error("Item not available to dispense")
        }
    }

};