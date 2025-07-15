#pragma once

#include "Item.hpp"

class ItemShelf{
    private:
        int shelfId;
        Item item;
        int quantity;
    
    public:
        ItemShelf(int _shelfId, const Item& _item, int _quantity) :
         shelfId(_shelfId), item(_item), quantity(_quantity) {}

         int getShelfId() const { return shelfId;}

         const Item& getItem() const {return item;}

         int getQuantity() const {return quantity;}

         bool isEmpty() const { return quantity ==0;}

         void devremntQuantity(){
            if(quantity >0 ) quantity--;
         }

         void refill(int count){
            quantity += count;
        }
};