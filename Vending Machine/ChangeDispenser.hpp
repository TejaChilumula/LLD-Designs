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

            // get the accepted denominations
            vector<int> denominations = Coin::getSupportedDenominations();
            //sort them high to low, so that
                // - we can give the max high denominations cash so that we can save more change
            sort(denominations.rbegin(), denominations.rend());

            for(int denom : denominations){
                int needed = amount / denom;
                int usable = min(needed, available[denom]);

                if(usable > 0){
                    result[denom] = usable;
                    amount -= denom*usable;  // remove that denom * num of notes can give of the denom
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