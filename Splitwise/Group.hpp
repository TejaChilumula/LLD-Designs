#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "Expense.hpp"
#include "User.hpp"
#include "ExpenseSplitStrategy.hpp"
#include "Balance.hpp"

class Group {
private:
    std::string id;
    std::string name;
    std::vector<User> members;
    std::vector<Expense> expenses;
    Balance balance;

public:
    Group(const std::string& id,
          const std::string& name,
          const std::vector<User>& initial)
        : id(id), name(name), members(initial) {}

    /*--------------- membership ---------------*/
    bool addMember(const User& user) {
        for (const auto& m : members)
            if (m.getId() == user.getId()) return false;
        members.push_back(user);
        return true;
    }

    /*--------------- add expense ---------------*/
    void addExpense(const Expense& exp, ExpenseSplitStrategy& strat) {
        expenses.push_back(exp);
        auto splits = strat.split(exp);
        for (const auto& s : splits) {
            if (s.getUser().getId() == exp.getPaidByUser().getId()) continue;
            balance.subtractAmount(s.getUser().getId(), s.getAmountOwed());   // debtor ↓
            balance.addAmount(    exp.getPaidByUser().getId(), s.getAmountOwed()); // payer ↑
        }
    }

    /*--------------- FIXED: partial settle-up ---------------*/
    bool settleUp(int fromId, int toId, double amount) {
        double fromBal = balance.getNetBalance(fromId);  // negative = owes
        double toBal   = balance.getNetBalance(toId);    // positive = gets

        if (fromBal >= 0 || toBal <= 0) return false;     // invalid

        amount = std::min(amount, -fromBal);  // can’t pay more than you owe
        amount = std::min(amount,  toBal);    // can’t receive more than you’re owed

        balance.addAmount(fromId,  amount);   // debtor gets closer to 0
        balance.subtractAmount(toId, amount); // creditor gets closer to 0
        return true;
    }

    /*--------------- getters ---------------*/
    const std::string&  getId()  const { return id; }
    const std::vector<User>& getMembers()  const { return members; }
    const std::vector<Expense>& getExpenses() const { return expenses; }
    const std::unordered_map<int,double>& getBalances() const { return balance.getSheet(); }
};
