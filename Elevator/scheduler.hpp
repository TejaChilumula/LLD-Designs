#pragma once
#include <vector>
#include <limits>
#include <cmath>
#include "elevator.hpp"
#include "floor.hpp"

class Scheduler {
public:
    virtual int assignElevator(const std::vector<Elevator*>& elevators, const Request& req) = 0;
    virtual ~Scheduler() = default;
};

class LookScheduler : public Scheduler {
public:
    int assignElevator(const std::vector<Elevator*>& elevators, const Request& req) override {
        int bestElevatorId = -1;
        int minCost = std::numeric_limits<int>::max();

        for (auto* e : elevators) {
            int cost = 0;
            int currentFloor = e->currentFloor;
            int reqFloor = req.floor.getNumber();  // Using Floor object now

            if (e->isIdle()) {
                cost = std::abs(currentFloor - reqFloor);
            } else if (e->direction == req.direction &&
                       ((req.direction == Direction::UP && currentFloor <= reqFloor) ||
                        (req.direction == Direction::DOWN && currentFloor >= reqFloor))) {
                cost = std::abs(currentFloor - reqFloor);
            } else {
                cost = std::abs(currentFloor - reqFloor) + 10; // Penalty for reversing
            }

            if (cost < minCost) {
                minCost = cost;
                bestElevatorId = e->id;
            }
        }
        return bestElevatorId;
    }
};
