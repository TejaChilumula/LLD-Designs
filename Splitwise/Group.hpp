#include <string>
#include <vector>
#include <unordered_map>
#include <stdexcept>
#include <cmath>
#include "Expense.hpp"
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

    void addExpense(const Expense& exp, ExpenseSplitType& strat){
        expenses.push_back(exp);
        auto splits = strat.split(exp);
        for(const auto& s: splits){
            if(s.getUser().getId() == exp.getPayer().getId()) continue;
            balances[s.getUser().getId()] -= s.getAmountOwed();
            balances[exp.getPayer().getId()]    += s.getAmountOwed();
        }
    }