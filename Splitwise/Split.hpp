#include <string>
#include <vector>
#include <stdexcept>
#include <cmath>
#include "User.hpp"

// ------------------- Split.hpp -------------------
class Split {
    private:
        User user;
        double amountOwe;
        double percentageShare = 0.0;

    public:
        Split(const User& user, double amount) : user(user), amountOwe(amount) {}
        Split(const User& user, double amount, double percentage) : user(user), amountOwe(amount), percentageShare(percentage) {}

        const User& getUser() const { return user; }
        double getAmountOwed() const { return amountOwe; }
        double getSharePercentage() const { return percentageShare; }

        void setAmountOwed(double amount){ amountOwe = amount; }
        void setSharePercentage(double percent) { percentageShare = percent;}

};
