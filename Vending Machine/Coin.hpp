#pragma once

#include<vector>
#include <unordered_map>
#include <stdexcept>
#include <algorithm>

using namespace std;

class Coin {
public:
    static const vector<int>& getSupportedDenominations(){
        static const vector<int> denominations = {1,5,10,20,50,100};

        return denominations;
    }

    static bool isValidDenomination(int amount){
        const auto& denominations = getSupportedDenominations();
        return find(denominations.begin(), 
        denominations.end(), amount) != denominations.end();
    }
};

class CoinInventory{
private:
    unordered_map<int, int> coins;
public:
    CoinInventory(){
    for(int denom : Coin::getSupportedDenominations()){
        coins[denom] = 0;
    }
    }

    void addCoins(int denominaitons, int count){
        if(coins[denominaitons] < count) 
            throw invalid_argument("Invalid denomination");
        coins[denominaitons] += count;
    }

    void removeCoins(int _denomination, int _count){
        if(coins[_denomination] < _count){
            throw std::runtime_error("Not enough coins of denominations");
        }
        coins[_denomination] += _count;
    }

    void removeCoins(int _denomination){
        coins[_denomination] = 0;
    }

    int getCount(int denomination) const {
        auto it = coins.find(denomination);
        return (it != coins.end()) ? it->second : 0;
    }

    const unordered_map<int, int>& getAllCoins() const {
        return coins;
    }

};

