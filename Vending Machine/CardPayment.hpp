#pragma once

#include "PaymentStrategy.hpp"
#include <unordered_map>
#include <stdexcept>

class CardPayment : public PaymentStrategy {
private:
    int cardBalance;  // For simulation only
    int insertedAmount;

public:
    CardPayment(int balance = 1000)
        : cardBalance(balance), insertedAmount(0) {}

    void insertMoney(int amount) override {
        if (amount <= 0) {
            throw std::invalid_argument("Invalid amount for card transaction");
        }
        insertedAmount += amount;
    }

    int getInsertedAmount() const override {
        return insertedAmount;
    }

    void reset() override {
        insertedAmount = 0;
    }

    std::unordered_map<int, int> collectChange(int price) override {
        if (insertedAmount < price) {
            throw std::runtime_error("Insufficient amount inserted");
        }

        int finalCharge = insertedAmount;
        int refund = insertedAmount - price;

        if (cardBalance < price) {
            throw std::runtime_error("Card declined due to insufficient balance");
        }

        cardBalance -= price;
        reset();

        return {}; // no physical coins returned
    }
};
