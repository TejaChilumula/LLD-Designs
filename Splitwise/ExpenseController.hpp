#ifndef EXPENSE_CONTROLLER_HPP
#define EXPENSE_CONTROLLER_HPP

#include <string>
#include <vector>
#include "Expense.hpp"
#include "ExpenseSplitStrategy.hpp"
#include "Group.hpp"
#include "BalanceSheetController.hpp"   // optional, if you want auto–simplification

class ExpenseController {
public:
    /**
     * Create an Expense after validating the split-details.
     * Throws std::invalid_argument if the split is inconsistent.
     */
    static Expense createExpense(const std::string& expenseId,
                                 const std::string& description,
                                 double amount,
                                 const std::vector<Split>& splitDetails,
                                 ExpenseSplitType splitType,
                                 const User& paidByUser)
    {
        // Pick the right strategy on the stack (no heap, no smart-ptrs)
        switch (splitType)
        {
            case ExpenseSplitType::EQUAL: {
                EqualSplitStrategy strat;
                // Validation happens inside split(); throw if inconsistent
                strat.split( Expense(expenseId, amount, paidByUser,
                                     splitType, splitDetails, description) );
                break;
            }
            case ExpenseSplitType::UNEQUAL: {
                UnequalSplitStrategy strat;
                strat.split( Expense(expenseId, amount, paidByUser,
                                     splitType, splitDetails, description) );
                break;
            }
            case ExpenseSplitType::PERCENTAGE: {
                PercentageSplitStrategy strat;
                strat.split( Expense(expenseId, amount, paidByUser,
                                     splitType, splitDetails, description) );
                break;
            }
            default:
                throw std::invalid_argument("Unsupported split type");
        }

        // If no exception => splits are valid.  Return the actual Expense object.
        return Expense(expenseId,          /* id            */
                       amount,             /* total amount  */
                       paidByUser,         /* payer         */
                       splitType,          /* split type    */
                       splitDetails,       /* participants  */
                       description);       /* optional note */
    }

    /**
     * Convenience helper: validates, creates, and pushes the expense into a group.
     *   - returns the freshly created Expense reference inside the group.
     */
    static const Expense& addExpenseToGroup(Group& group,
                                            const std::string& expenseId,
                                            const std::string& description,
                                            double amount,
                                            const std::vector<Split>& splitDetails,
                                            ExpenseSplitType splitType,
                                            const User& paidByUser)
    {
        Expense expense = createExpense(expenseId, description, amount,
                                        splitDetails, splitType, paidByUser);

        // Pick strategy again just for application to balances
        switch (splitType)
        {
            case ExpenseSplitType::EQUAL: {
                static EqualSplitStrategy strat;   // static so lifetime > call
                group.addExpense(expense, strat);
                break;
            }
            case ExpenseSplitType::UNEQUAL: {
                static UnequalSplitStrategy strat;
                group.addExpense(expense, strat);
                break;
            }
            case ExpenseSplitType::PERCENTAGE: {
                static PercentageSplitStrategy strat;
                group.addExpense(expense, strat);
                break;
            }
        }
        return group.getExpenses().back();  // handy if caller needs the Expense
    }
};

#endif // EXPENSE_CONTROLLER_HPP
