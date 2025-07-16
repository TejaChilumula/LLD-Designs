#pragma once

#include <vector>
#include <unordered_map>
#include <stdexcept>
#include <algorithm>
#include "Coin.hpp"

class ChangeDispenser {
    private:
        CoinInventory& coinInventory;
    
    public:
        ChangeDispenser(CoinInventory& inventory): coinInventory(inventory) {}


        // get the existing change
        unordered_map<int, int> getChange(int amount){
            unordered_map<int, int> result;
            auto available = coinInventory.getAllCoins();

            
            vector<int> denominations = Coin::getSupportedDenominations();
            sort(denominations.rbegin(), denominations.rend());

            for(int denom : denominations){
                int needed = amount / denom;
                int usable = min(needed, available[denom]);

                if(usable > 0){
                    result[denom] = usable;
                    amount -= denom*usable;
                }
            }

            if(amount != 0)
                throw runtime_error("Insufficient change availabel");

            for(const auto& [denom, count] : result){
                coinInventory.removeCoins(denom, count);
            }

            return result;
        }

        void refill(int denomination, int count){
            coinInventory.addCoins(denomination, count);
        }

    };