#include <iostream>
#include "Splitwise.hpp"
#include "ExpenseController.hpp"
#include "EqualSplitStrategy.hpp"  // Only for default fallback
#include "Split.hpp"

int main() {
    Splitwise& splitwise = Splitwise::instance();
    auto& userCtl = splitwise.users();
    auto& groupCtl = splitwise.groups();
    auto& balanceCtl = splitwise.balances();

    // Register users
    userCtl.addUser(User(1, "Alice"));
    userCtl.addUser(User(2, "Bob"));
    userCtl.addUser(User(3, "Charlie"));
    userCtl.addUser(User(4, "David"));

    // Create a group with Alice
    Group& group = groupCtl.createNewGroup("G1", "Trip", *userCtl.getUser(1));
    group.addMember(*userCtl.getUser(2));
    group.addMember(*userCtl.getUser(3));
    group.addMember(*userCtl.getUser(4));

    // ExpenseController handles expense creation and update
    ExpenseController expenseCtl;

    // Expense 1: Equal split among 3
    std::vector<Split> breakfastSplits = {
        Split(*userCtl.getUser(1), 0), // Alice
        Split(*userCtl.getUser(2), 0), // Bob
        Split(*userCtl.getUser(3), 0)  // Charlie
    };
    expenseCtl.addExpenseToGroup(group, "EXP001", "Breakfast", 900, breakfastSplits, ExpenseSplitType::EQUAL, *userCtl.getUser(1));

    // Expense 2: Unequal split
    std::vector<Split> lunchSplits = {
        Split(*userCtl.getUser(1), 400),
        Split(*userCtl.getUser(2), 300),
        Split(*userCtl.getUser(3), 200)
    };
    expenseCtl.addExpenseToGroup(group, "EXP002", "Lunch", 900, lunchSplits, ExpenseSplitType::UNEQUAL, *userCtl.getUser(1));

    // Expense 3: Percentage split
    std::vector<Split> dinnerSplits = {
        Split(*userCtl.getUser(1), 0, 40),
        Split(*userCtl.getUser(2), 0, 30),
        Split(*userCtl.getUser(3), 0, 20),
        Split(*userCtl.getUser(4), 0, 10)
    };
    expenseCtl.addExpenseToGroup(group, "EXP003", "Dinner", 1000, dinnerSplits, ExpenseSplitType::PERCENTAGE, *userCtl.getUser(4));

    // Print simplified debts
    auto transactions = balanceCtl.getSimplifiedDebts(group.getBalances());
    for (const auto& txn : transactions) {
        std::cout << txn << std::endl;
    }

    return 0;
}
