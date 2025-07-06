#ifndef EXPENSE_HPP
#define EXPENSE_HPP

#include <string>
#include <vector>
#include "User.hpp"
#include "Split.hpp"

enum class ExpenseSplitType{
    EQUAL,
    UNEQUAL,
    PERCENTAGE
};

class Expense{
    private:
    std::string expenseId;
    std::string description;
    double expenseAmount;
    User paidByUser;
    ExpenseSplitType splitType;
    std::vector<Split> splitDetails;

    public:
        Expense(const std::string& expenseId,
        double amount, 
        const User& paidByUser,
        ExpenseSplitType splitType,
        const std::vector<Split>& splitDetails,
        const std::string& description=""):
        expenseId(expenseId),
          expenseAmount(amount),
          paidByUser(paidByUser),
          splitType(splitType),
          splitDetails(splitDetails),
          description(description) {}

    const std::string&getExpenseId() const { return expenseId;}
    const std::string& getDescription() const {return description;}
    double getAmount() const { return expenseAmount;}
    const User& getPaidByUser() const { return paidByUser; }
    ExpenseSplitType getSplitType() const { return splitType; }
    const std::vector<Split>& getSplits() const { return splitDetails; }
);
     
#endif