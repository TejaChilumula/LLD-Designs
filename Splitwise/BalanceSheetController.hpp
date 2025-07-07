#ifndef BALANCE_SHEET_CONTROLLER_HPP
#define BALANCE_SHEET_CONTROLLER_HPP

#include <vector>
#include <unordered_map>
#include <cmath>
#include <algorithm>
#include <map>
#include "Transaction.hpp"
#include "BalanceSummary.hpp"

class BalanceSheetController {
private:
    // Track manual settle-ups between users
    std::vector<Transaction> manualSettlements;

public:
    // Add a settle-up transaction (e.g., partial payment)
    void settleUp(int fromUserId, int toUserId, double amount) {
        manualSettlements.emplace_back(fromUserId, toUserId, amount);
    }

    // Simplify all balances after settle-ups
    BalanceSummary simplifyBalances(const std::unordered_map<int, double>& originalBalances) {
        std::unordered_map<int, double> balances = originalBalances;

        // Apply manual settle-up transactions
        for (const auto& txn : manualSettlements) {
            balances[txn.fromUserId] -= txn.amount;
            balances[txn.toUserId]   += txn.amount;
        }

        BalanceSummary summary;
        std::vector<std::pair<int, double>> debtors, creditors;

        double totalCredits = 0.0;

        for (const auto& [id, amount] : balances) {
            summary.netBalance[id] = amount;

            if (std::fabs(amount) < 1e-6) continue;

            if (amount < 0) {
                debtors.emplace_back(id, -amount);
                summary.totalYouOwe += -amount;
            } else {
                creditors.emplace_back(id, amount);
                summary.totalYouGetBack += amount;
                totalCredits += amount;
            }
        }

        summary.totalExpense = totalCredits;

        // Simplify debtors and creditors
        size_t i = 0, j = 0;
        while (i < debtors.size() && j < creditors.size()) {
            double minAmount = std::min(debtors[i].second, creditors[j].second);

            summary.transactions.emplace_back(debtors[i].first, creditors[j].first, minAmount);

            debtors[i].second -= minAmount;
            creditors[j].second -= minAmount;

            if (std::fabs(debtors[i].second) < 1e-6) ++i;
            if (std::fabs(creditors[j].second) < 1e-6) ++j;
        }

        return summary;
    }

    // Get per-user breakdown of who they owe or get money from
    std::unordered_map<int, std::vector<Transaction>> getPendingTransactionsPerUser(const BalanceSummary& summary) {
        std::unordered_map<int, std::vector<Transaction>> perUser;
        for (const auto& txn : summary.transactions) {
            perUser[txn.fromUserId].push_back(txn);
            perUser[txn.toUserId].push_back(txn);  // Optional for reverse lookup
        }
        return perUser;
    }

    // Clear all settle-ups (useful between test cases or groups)
    void clearSettlements() {
        manualSettlements.clear();
    }
};

#endif // BALANCE_SHEET_CONTROLLER_HPP
