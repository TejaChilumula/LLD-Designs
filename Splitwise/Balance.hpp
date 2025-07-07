#pragma once
#ifndef BALANCE_HPP
#define BALANCE_HPP

#include <unordered_map>
#include "User.hpp"

class Balance {
private:
    std::unordered_map<int, double> balanceSheet;

public:
    void addAmount(int userId, double amount) {
        balanceSheet[userId] += amount;
    }

    void subtractAmount(int userId, double amount) {
        balanceSheet[userId] -= amount;
    }

    double getNetBalance(int userId) const {
        auto it = balanceSheet.find(userId);
        return (it != balanceSheet.end()) ? it->second : 0.0;
    }

    const std::unordered_map<int, double>& getSheet() const {
        return balanceSheet;
    }
};

#endif // BALANCE_HPP
