#pragma once

#include<unordered_map>
#include<stdexcept>
#include "PaymentStrategy.hpp"
#include "Coin.hpp"
#include "ChangeDispenser.hpp"

using namespace std;

class CashPayment : public PaymentStrategy{
    private:
        CoinInventory& coinInventory;
        ChangeDispenser& changeDispenser;
        unordered_map<int, int> insertedCoins;
        int totalInsterted = 0;
    
    public:
        CashPayment(CoinInventory& _inventory, ChangeDispenser& _dispenser) : 
        coinInventory(_inventory), changeDispenser(_dispenser){}

        void insertMoney(int amount) override {
            if(!Coin::isValidDenomination(amount)){
                throw invalid_argument("Invalid coin inserted");
            }

            insertedCoins[amount]++;
            totalInsterted += amount;
            coinInventory.addCoins(amount, 1);
        }

        int getInsertedAmount() const override{
            return totalInsterted;
        }

        void reset() override{
            insertedCoins.clear();
            totalInsterted = 0;
        }

        unordered_map<int, int> collectChange(int price) override{
            if(totalInsterted < price){
                throw runtime_error("Insufficient amount inserted");
            }

            int change = totalInsterted - price;
            
            auto changeCoins = changeDispenser.getChange(change);
            reset();
            return changeCoins;
        }
};