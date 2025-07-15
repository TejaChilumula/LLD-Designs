#pragma once

#include<string>
#include "ItemType.hpp"

using namespace std;

class Item{
private:
        int id;
        string name;
        double price;
        ItemType type;

public:
    Item(int _id, const string& _name, double _price, ItemType _type):
    id(_id), name(_name), price(_price), type(_type) {}

    int getId() const { return id;}
    const string& getName() const { return name;}
    double getPrice() const {return price;}
    ItemType getType() const{return type;}
  
};