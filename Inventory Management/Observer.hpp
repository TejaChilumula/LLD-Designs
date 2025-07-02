#pragma once
#include "Item.hpp"
#include<string>

class LowStockObserver{
    public:
    virtual void onLowStock(const Item& item, const std::string& warehouse, int qty) = 0;
    virtual ~LowStockObserver() = default;
};
