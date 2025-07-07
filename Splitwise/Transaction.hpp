#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP

class Transaction {
public:
    int fromUserId;
    int toUserId;
    double amount;

    Transaction(int from, int to, double amount)
        : fromUserId(from), toUserId(to), amount(amount) {}
};

#endif // TRANSACTION_HPP
