#pragma once

#include<vector>
#include<unordered_map>

using namespace std;

class PaymentStrategy{
    public:
        virtual void insertMoney(int amount) = 0;
        virtual int getInsertedAmount() const = 0;
        virtual void reset() = 0;

        virtual unordered_map<int, int> collectChange(int price) = 0;

        virtual ~PaymentStrategy(){}
};
