#pragma once
#include "strategy.hpp"

class SCANStrategy : public Strategy {
public:
    int getNextStop(Elevator* elevator) override {
        if (elevator->requests.empty())
            return elevator->currentFloor;

        int currentFloor = elevator->currentFloor;
        Direction dir = elevator->direction;

        int candidate = -1;
        // Move in current direction first
        for (const auto& req : elevator->requests) {
            Floor floor = req.floor;
            int f = floor.getNumber();
            if (dir == Direction::UP && f >= currentFloor) {
                if (candidate == -1 || f < candidate) candidate = f;
            } else if (dir == Direction::DOWN && f <= currentFloor) {
                if (candidate == -1 || f > candidate) candidate = f;
            }
        }

        if (candidate != -1)
            return candidate;

        // No requests in current direction, reverse and find closest
        for (const auto& req : elevator->requests) {
            Floor floor = req.floor;
            int f = floor.getNumber();
            if (dir == Direction::UP && f < currentFloor) {
                if (candidate == -1 || f > candidate) candidate = f;
            } else if (dir == Direction::DOWN && f > currentFloor) {
                if (candidate == -1 || f < candidate) candidate = f;
            }
        }

        return (candidate != -1) ? candidate : currentFloor;
    }
};
