#pragma once

#include <unordered_map>
#include <vector>
#include <stdexcept>
#include "ItemShelf.hpp"

class Inventory {
private:
    std::unordered_map<int, ItemShelf> shelves;

public:
    void addShelf(const ItemShelf& shelf) {
        shelves[shelf.getShelfId()] = shelf;
    }

    bool isAvailable(int shelfId) const {
        auto it = shelves.find(shelfId);
        return it != shelves.end() && !it->second.isEmpty();
    }

    const Item& getItem(int shelfId) const {
        auto it = shelves.find(shelfId);
        if (it == shelves.end()) {
            throw std::runtime_error("Invalid shelf ID");
        }
        return it->second.getItem();
    }

    void dispenseItem(int shelfId) {
        auto it = shelves.find(shelfId);
        if (it == shelves.end()) {
            throw std::runtime_error("Invalid shelf ID");
        }
        if (it->second.isEmpty()) {
            throw std::runtime_error("Item is already out of stock");
        }
        it->second.decrementQuantity();
    }

    void refillShelf(int shelfId, int quantity) {
        auto it = shelves.find(shelfId);
        if (it == shelves.end()) {
            throw std::runtime_error("Invalid shelf ID");
        }
        it->second.refill(quantity);
    }

    std::vector<ItemShelf> getAllShelves() const {
        std::vector<ItemShelf> result;
        result.reserve(shelves.size());
        for (const auto& pair : shelves) {
            result.push_back(pair.second); // Copies are OK here
        }
        return result;
    }
};
