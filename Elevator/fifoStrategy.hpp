#pragma once
#include "strategy.hpp"

class FIFOStrategy : public Strategy {
public:
    int getNextStop(Elevator* elevator) override {
        if (elevator->requests.empty())
            return elevator->currentFloor; // Assuming currentFloor is int

        // Return the floor of the first request
        return elevator->requests.front().floor.getNumber(); // Assuming floor is int
    }
};
