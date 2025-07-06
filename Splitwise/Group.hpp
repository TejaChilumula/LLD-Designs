#include <string>
#include <vector>
#include <unordered_map>
#include <stdexcept>
#include <cmath>

#include "Expense.hpp"
#include "ExpenseSplitStrategy.hpp"
#include "User.hpp"

class Group {
    std::string                     id;
    std::string                     name;
    std::vector<User>               members;
    std::vector<Expense>            expenses;
    std::unordered_map<int,double>  balances; 

    public:
        Group(const std::string& id, const std::string& name, const std::vector<User>& initial)
        : id(id), name(name), members(initial) {}

    bool addMember(const User& user){
        for(const auto& m : members) if(m.getId() == user.getId()) return false;
        members.push_back(user);
        return true;
    }

    void addExpense(const Expense& exp, ExpenseSplitStrategy& strat){
        expenses.push_back(exp);
        auto splits = strat.split(exp);
        for(const auto& s: splits){
            if(s.getUser().getId() == exp.getPaidByUser().getId()) continue;
            balances[s.getUser().getId()] -= s.getAmountOwed();
            balances[exp.getPaidByUser().getId()]    += s.getAmountOwed();
        }
    }


    const std::unordered_map<int, double>& getBalances() const {
        return balances;
    }

    const std::vector<User>& getMembers() const {
        return members;
    }
};
