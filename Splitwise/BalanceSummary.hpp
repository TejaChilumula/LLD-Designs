#ifndef BALANCE_SUMMARY_HPP
#define BALANCE_SUMMARY_HPP

#include <unordered_map>
#include "Balance.hpp"
#include "Transaction.hpp"
#include<vector>

class BalanceSummary {
public:
    double totalExpense = 0;
    double totalPaid = 0;
    double totalYouOwe = 0;
    double totalYouGetBack = 0;

    std::unordered_map<int, double> netBalance;
    std::vector<Transaction> transactions;

    BalanceSummary() = default;
};

#endif // BALANCE_SUMMARY_HPP
