#ifndef SPLITWISE_HPP
#define SPLITWISE_HPP

#include "UserController.hpp"
#include "GroupController.hpp"
#include "BalanceSheetController.hpp"

class Splitwise {
private:
    UserController userController;
    GroupController groupController;
    BalanceSheetController balanceController;

    Splitwise() = default;

public:
    static Splitwise& instance() {
        static Splitwise instance;
        return instance;
    }

    UserController& users() { return userController; }
    GroupController& groups() { return groupController; }
    BalanceSheetController& balances() { return balanceController; }

    Splitwise(const Splitwise&) = delete;
    Splitwise& operator=(const Splitwise&) = delete;
};

#endif // SPLITWISE_HPP
