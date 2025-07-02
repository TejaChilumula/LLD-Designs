#pragma once
#include "Item.hpp"
#include <vector>
#include <chrono>
#include <atomic>
#include <cstdint>

enum class OrderType { Purchase, Sale};

struct OrderLine
{
    Item::Id itemId;
    int quantity;
    double priceEach;
};

class Order{


   
    public:
    using Id = std::uint64_t;

   Order(OrderType type, const std::string& warehouse, const std::vector<OrderLine>& lines)
        : _id(generateId()), _type(type), _warehouse(warehouse),
          _timestamp(std::chrono::system_clock::now()), _lines(lines) {}

          Id id() const{return _id;}
          OrderType type() const{ return _type;}
          const std::string& warehouse() const { return _warehouse;}
          const std::vector<OrderLine>& lines() const {return _lines;}

     private:
        static Id generateId(){
            static std::atomic<Id>counter{1};
            return counter++;
        }
    Id _id;
    OrderType _type;
    std::string _warehouse;
    std::chrono::system_clock::time_point _timestamp;
    std::vector<OrderLine> _lines;

};
