// PricingStrategy.hpp
#ifndef PRICINGSTRATEGY_HPP
#define PRICINGSTRATEGY_HPP

class PricingStrategy {
public:
    virtual double calculate(long long durationMinutes) const = 0;
    virtual ~PricingStrategy() {}
};

class FlatRateStrategy : public PricingStrategy {
public:
    double calculate(long long durationMinutes) const override {
        return durationMinutes * 0.5;
    }
};

class HourlyRateStrategy : public PricingStrategy {
public:
    double calculate(long long durationMinutes) const override {
        return ((durationMinutes + 59) / 60) * 10.0; // Rs. 10 per hour
    }
};

#endif