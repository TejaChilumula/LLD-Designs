#pragma once
#include "Balance.hpp"
#include<vector>
#include<string>
#include<iostream>

class BalanceSheetController{
    public:
        static std::vector<std::string> getSimplifiedDebts(
            const std::unordered_map<int, double>& balances){
                std::vector<std::pair<int,double>> debtors, creditors;

                for(const auto& [id, amount] : balances){
                    if(std::fabs(amount) < 1e-6) continue;
                    if(amount < 0) debtors.push_back({id, -amount});
                    else creditors.push_back({id, amount});
                    
                }

                size_t i=0, j=0;
                std::vector<std::string> transactions;

                while(i<debtors.size() && j < creditors.size()){
                    double minAmount = std::min(debtors[i].second, creditors[j].second);
                    transactions.push_back("User " + std::to_string(debtors[i].first) +
                                   " pays User " + std::to_string(creditors[j].first) +
                                   " Rs." + std::to_string(minAmount));

                    debtors[i].second -= minAmount;
                    creditors[j].second -= minAmount;

                    if (std::fabs(debtors[i].second) < 1e-6) ++i;
                    if (std::fabs(creditors[j].second) < 1e-6) ++j;
                }

                return transactions;
    }
               
};
