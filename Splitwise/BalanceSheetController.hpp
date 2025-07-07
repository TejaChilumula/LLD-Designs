#ifndef BALANCE_SHEET_CONTROLLER_HPP
#define BALANCE_SHEET_CONTROLLER_HPP

#include <vector>
#include <unordered_map>
#include <cmath>
#include <algorithm>
#include "Transaction.hpp"
#include "BalanceSummary.hpp"

class BalanceSheetController {
public:
    static BalanceSummary simplifyBalances(const std::unordered_map<int, double>& balances) {
        BalanceSummary summary;
        std::vector<std::pair<int, double>> debtors, creditors;

        for (const auto& [id, amount] : balances) {
            summary.netBalance[id] = amount;
            summary.totalExpense += std::fabs(amount);

            if (std::fabs(amount) < 1e-6) continue;
            if (amount < 0) {
                debtors.emplace_back(id, -amount);
                summary.totalYouOwe += -amount;
            } else {
                creditors.emplace_back(id, amount);
                summary.totalYouGetBack += amount;
            }
        }

        // Simplify debts
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
};

#endif // BALANCE_SHEET_CONTROLLER_HPP
