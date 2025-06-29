#pragma once
#include "strategy.hpp"
#include "floor.hpp"

class LookStrategy : public Strategy {
public:
    int getNextStop(Elevator* elevator) override {
        if (elevator->requests.empty()) return elevator->currentFloor;

        int currentFloor = elevator->currentFloor;
        int primaryFloor = elevator->requests.front().floor.getNumber();
        Direction travelDir = (primaryFloor > currentFloor) ? Direction::UP : Direction::DOWN;
        int candidate = -1;

        for (const auto& req : elevator->requests) {
            int f = req.floor.getNumber();
            bool internal = (req.type == RequestType::INTERNAL);

            if (travelDir == Direction::UP) {
                if (f > currentFloor && f <= primaryFloor) {
                    if (internal || (!internal && req.direction == Direction::UP)) {
                        if (candidate == -1 || f < candidate)
                            candidate = f;
                    }
                }
            } else {
                if (f < currentFloor && f >= primaryFloor) {
                    if (internal || (!internal && req.direction == Direction::DOWN)) {
                        if (candidate == -1 || f > candidate)
                            candidate = f;
                    }
                }
            }
        }

        return (candidate != -1) ? candidate : primaryFloor;
    }
};
