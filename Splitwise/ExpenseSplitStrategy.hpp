#include <string>
#include <vector>
#include <stdexcept>
#include <cmath>
#include "User.hpp"
#include "Split.hpp"

class ExpenseSplitStrategy{
    public:
        virtual std::vector<Split> split(const Expense& expense) = 0;
        virtual ~ExpenseSplitStrategy() {}

};

class EqualSplitStrategy : public ExpenseSplitStrategy {
    public:
        std::vector<Split> split(const Expense& expense) override{
            const auto& users = expense.getSplits();
            double amountPerUser = expense.getAmount()/ users.size();
            std::vector<Split> result;
            for(const auto&s: users){
                result.emplace_back(s.getUser(), amountPerUser);
            }
            return result;
        }
};


class PercentageSplitStrategy : public ExpenseSplitStrategy{
    public:
        std::vector<Split> split(const Expense& expense) override {
            doubl total = 0;
            for(cosnt auto& s : expense.getSplits()) total += s.getSharePercentage();
            if (std::fabs(total - 100.0) > 1e-6){
                throw std::invalid_argument("Total percentage must sum to 100");
            }

            std::vector<Split> result;
            for(const auto& s : expense.getSplit()) {
                double share = expense.getAmount()*(s.getSharePercentage() / 100.0);
                result.emplace_back(s.getUser().share);
            }
            return result;
        }
};

class UnequalSplitStrategy : public ExpenseSplitStrategy {
public:
    std::vector<Split> split(const Expense& expense) override {
        double total = 0;
        for (const auto& s : expense.getSplits()) total += s.getAmountOwed();
        if (std::fabs(total - expense.getAmount()) > 1e-6) {
            throw std::invalid_argument("Split amounts must sum to total expense");
        }
        return expense.getSplits();
    }
};

#endif // EXPENSE_HPP
