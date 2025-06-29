#pragma once
#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include "observer.hpp"
#include "strategy.hpp"
#include "floor.hpp"  // include Floor class

enum class Direction { UP, DOWN, IDLE };
enum class ElevatorState { IDLE, MOVING, STOPPED, MAINTENANCE };
enum class RequestType { INTERNAL, EXTERNAL };

inline int toInt(Direction d) {
    return (d == Direction::UP) ? 1 : (d == Direction::DOWN ? -1 : 0);
}

struct Request {
    Floor floor;
    Direction direction;
    RequestType type;
    Request(Floor f, Direction d, RequestType t) : floor(f), direction(d), type(t) {}
};

class Elevator {
public:
    int id;
    int currentFloor;
    Direction direction;
    ElevatorState state;
    std::deque<Request> requests;
    std::vector<ElevatorObserver*> observers;
    Strategy* strategy;  // Pointer to scheduling strategy

    Elevator(int i, Strategy* strat) 
        : id(i), currentFloor(0), direction(Direction::IDLE), 
          state(ElevatorState::IDLE), strategy(strat) {}

    void addRequest(const Request& r) {
        requests.push_back(r);
        updateDirectionAndState();
    }

    void step() {
        switch (state) {
            case ElevatorState::IDLE:
                break;
            case ElevatorState::MOVING:
                currentFloor += toInt(direction);
                notifyFloorChange();
                for (auto it = requests.begin(); it != requests.end(); ++it) {
                    if (it->floor.getNumber() == currentFloor) {
                        std::cout << "[Elevator " << id << "] Stopping at floor " << currentFloor << std::endl;
                        requests.erase(it);
                        state = ElevatorState::STOPPED;
                        notifyStateChange();
                        return;
                    }
                }
                break;
            case ElevatorState::STOPPED:
                updateDirectionAndState();
                break;
            case ElevatorState::MAINTENANCE:
                std::cout << "[Elevator " << id << "] In maintenance mode." << std::endl;
                break;
        }
    }

    bool isIdle() const {
        return state == ElevatorState::IDLE;
    }

    void updateDirectionAndState() {
        if (requests.empty()) {
            direction = Direction::IDLE;
            state = ElevatorState::IDLE;
            notifyStateChange();
            return;
        }

        int nextStop = strategy->getNextStop(this);
        if (nextStop > currentFloor)
            direction = Direction::UP;
        else if (nextStop < currentFloor)
            direction = Direction::DOWN;
        else
            direction = Direction::IDLE;

        state = (direction == Direction::IDLE) ? ElevatorState::STOPPED : ElevatorState::MOVING;
        notifyStateChange();
    }

    void addObserver(ElevatorObserver* obs) {
        observers.push_back(obs);
    }

    void notifyFloorChange() {
        for (auto* obs : observers) {
            obs->onFloorChange(id, currentFloor);
        }
    }

    void notifyStateChange() {
        for (auto* obs : observers) {
            obs->onStateChange(id, state);
        }
    }

    bool isAtFloor(int floor) const {
        return currentFloor == floor && state == ElevatorState::STOPPED;
    }

    int getId() const {
        return id;
    }
};
