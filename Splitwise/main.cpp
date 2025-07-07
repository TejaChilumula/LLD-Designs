#include <iostream>
#include <iomanip>
#include "Splitwise.hpp"
#include "ExpenseController.hpp"
#include "BalanceSheetController.hpp"
#include "UserController.hpp"
#include "Split.hpp"

void printDetailedUserBreakdown(const BalanceSummary& summary, const UserController& uc) {
    std::cout << "\n===== Per-User Detailed Breakdown =====\n";

    std::unordered_map<int, std::vector<std::pair<int, double>>> owedFrom; // who owes me
    std::unordered_map<int, std::vector<std::pair<int, double>>> owesTo;   // whom I owe

    for (const auto& txn : summary.transactions) {
        owesTo[txn.fromUserId].emplace_back(txn.toUserId, txn.amount);
        owedFrom[txn.toUserId].emplace_back(txn.fromUserId, txn.amount);
    }

    for (const auto& [uid, net] : summary.netBalance) {
        const std::string& name = uc.getUser(uid)->getName();
        std::cout << "\nUser: " << name << " (ID: " << uid << ")\n";

        if (owedFrom.count(uid)) {
            std::cout << "  Gets back:\n";
            for (const auto& [fromId, amt] : owedFrom[uid]) {
                std::cout << "    → ₹" << amt << " from " << uc.getUser(fromId)->getName() << "  [Group Expense]\n";
            }
        }

        if (owesTo.count(uid)) {
            std::cout << "  Owes:\n";
            for (const auto& [toId, amt] : owesTo[uid]) {
                std::cout << "    → ₹" << amt << " to " << uc.getUser(toId)->getName() << "  [Group Expense]\n";
            }
        }

        std::cout << "-------------------------------------------\n";
        std::cout << "  Net Balance: ₹" << net << '\n';
    }
    std::cout << std::endl;
}


/* ---------- Pretty-printers ---------- */
void printSummary(const std::string& title, const BalanceSummary& sum)
{
    std::cout << "\n===== " << title << " =====\n";
    std::cout << "Total Group Expense: Rs." << sum.totalExpense   << '\n'
              << "Total You Owe      : Rs." << sum.totalYouOwe    << '\n'
              << "Total You Get Back : Rs." << sum.totalYouGetBack<< "\n\n";

    std::cout << "-- Simplified Transactions --\n";
    for (const auto& t : sum.transactions)
        std::cout << "User " << t.fromUserId
                  << " pays User " << t.toUserId
                  << " Rs." << t.amount << '\n';

    std::cout << "\n-- Net Balances --\n";
    for (const auto& [id, amt] : sum.netBalance)
        std::cout << "User " << id << " => " << amt << '\n';

    std::cout << std::endl;
}

void printPending(const std::unordered_map<int, std::vector<Transaction>>& pending)
{
    std::cout << "\n-- Per-User Pending Transactions --\n";
    for (const auto& [uid, list] : pending) {
        std::cout << "User " << uid << ":\n";
        for (const auto& txn : list) {
            if (txn.fromUserId == uid)
                std::cout << "  owes  Rs." << txn.amount
                          << " to User "  << txn.toUserId   << '\n';
            else
                std::cout << "  gets  Rs." << txn.amount
                          << " from User "<< txn.fromUserId << '\n';
        }
    }
    std::cout << std::endl;
}

/* ---------- Helper: log snapshot after each action ---------- */
void printInterim(const std::string& label,
                  Group& g,
                  BalanceSheetController& bsc)
{
    BalanceSummary snap = bsc.simplifyBalances(g.getBalances());
    printSummary(label, snap);
}

int main()
{
    /* ----- Setup: users, group, controllers ----- */
    auto& sw = Splitwise::instance();
    auto& uc = sw.users();
    auto& gc = sw.groups();

    uc.addUser(User(1,"Alice"));
    uc.addUser(User(2,"Bob"));
    uc.addUser(User(3,"Charlie"));
    uc.addUser(User(4,"David"));

    Group& g = gc.createNewGroup("G1","Trip", *uc.getUser(1));
    g.addMember(*uc.getUser(2));
    g.addMember(*uc.getUser(3));
    g.addMember(*uc.getUser(4));

    ExpenseController      ec;
    BalanceSheetController bsc;

    /* ----- Expense 1: Breakfast (equal) ----- */
    ec.addExpenseToGroup(g,"EXP1","Breakfast",900,
        {Split(*uc.getUser(1),0),Split(*uc.getUser(2),0),Split(*uc.getUser(3),0)},
        ExpenseSplitType::EQUAL,*uc.getUser(1));
    printInterim("After Breakfast Expense", g, bsc);

    /* ----- Expense 2: Lunch (unequal) ----- */
    ec.addExpenseToGroup(g,"EXP2","Lunch",900,
        {Split(*uc.getUser(1),400),Split(*uc.getUser(2),300),Split(*uc.getUser(3),200)},
        ExpenseSplitType::UNEQUAL,*uc.getUser(1));
    printInterim("After Lunch Expense", g, bsc);

    /* ----- Expense 3: Dinner (percentage) ----- */
    ec.addExpenseToGroup(g,"EXP3","Dinner",1000,
        {Split(*uc.getUser(1),0,40),Split(*uc.getUser(2),0,30),
         Split(*uc.getUser(3),0,20),Split(*uc.getUser(4),0,10)},
        ExpenseSplitType::PERCENTAGE,*uc.getUser(4));
    printInterim("After Dinner Expense", g, bsc);

    /* ----- Four mini two-person expenses (Bob paid) ----- */
    struct Mini{double amt; std::string tag;};
    std::vector<Mini> minis{{120,"Coffee"},{70,"Snacks"},{160,"Cab"},{90,"Book"}};
    for(size_t i=0;i<minis.size();++i){
        double half = minis[i].amt/2.0;
        ec.addExpenseToGroup(g,"M"+std::to_string(i),minis[i].tag,minis[i].amt,
            {Split(*uc.getUser(1),half),Split(*uc.getUser(2),half)},
            ExpenseSplitType::UNEQUAL,*uc.getUser(2));   // Bob paid
        printInterim("After "+minis[i].tag+" Expense", g, bsc);
    }

    /* ---------- Manual settle-ups ---------- */
    bsc.settleUp(2,1,200);   // Bob → Alice
    printInterim("After Bob paid Alice Rs.200", g, bsc);

    bsc.settleUp(3,4,150);   // Charlie → David
    printInterim("After Charlie paid David Rs.150", g, bsc);

    bsc.settleUp(3,1,100);   // Charlie → Alice
    printInterim("After Charlie paid Alice Rs.100", g, bsc);

    /* ---------- Final pending list ---------- */
    BalanceSummary finalSummary = bsc.simplifyBalances(g.getBalances());
    printDetailedUserBreakdown(finalSummary, uc);
    auto pending = bsc.getPendingTransactionsPerUser(finalSummary);
    printPending(pending);

    return 0;
}
