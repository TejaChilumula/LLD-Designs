#pragma once
#include<set>

class ReplenishmentStrategy {
public:
    virtual bool shouldReplenish(int currentQty) const = 0;
    virtual int reorderAmount() const = 0;
    virtual ~ReplenishmentStrategy() = default;
};

class FixedThresholdReplenishment : public ReplenishmentStrategy {
    int threshold_;
    int reorderQty_;
public:
    FixedThresholdReplenishment(int threshold, int reorderQty)
        : threshold_(threshold), reorderQty_(reorderQty) {}

    bool shouldReplenish(int currentQty) const override {
        return currentQty < threshold_;
    }

    int reorderAmount() const override {
        return reorderQty_;
    }
};
// Can include Dynamic methods