#pragma once
#include "Item.hpp"
#include <unordered_map>
#include <vector>
#include <string>

class Warehouse{
    private:
    std:: string _name;
    std::unordered_map<Item::Id, int> _stock;
    public:
    Warehouse(const std::string& name) : _name(name){}

    void addStock(Item::Id id, int qty) { _stock[id] += qty;}

    bool removeStock(Item::Id id, int qty){
        if(_stock[id] < qty) return false;
        _stock[id] -= qty;
        return true;
    }

    int getStock(Item::Id id) const{
        auto it = _stock.find(id);
        return it == _stock.end() ? 0 : it->second;
    }

    const std::string& name() const {return _name;}
    const std::unordered_map<Item::Id, int>& allStock() const {return _stock;}


};