#pragma once
#ifndef BALANCE_HPP
#define BALANCE_HPP

#include<unordered_map>
#include "User.hpp"

class Balance {
    private:
        std::unordered_map<int, double> balanceSheet;
    public:
        void addAmount(int userId, double amount){
            balanceSheet[userId] += amount;
        }

        void subtractAmount(int userId, double amount){
            balanceSheet[userId] -= amount;
        }

        const std::unordered_map<int, double>& getSheet() const{
            return balanceSheet;
        }
};
#endif