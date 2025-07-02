#pragma once

class PricingStrategy{

    public:
        virtual double compute(double basePrice, int quantity) const = 0;
        virtual ~PricingStrategy() = default;

};
class FlatPricing : public PricingStrategy
{   /* data */
public:
    double compute(double basePrice, int) const override{
        return basePrice;
    }
};

class BulkPricing : public PricingStrategy{
    public:
        double compute(double basePrice, int qty) const override {
            return qty >= 100 ? basePrice*0.9 : basePrice;
        }
};