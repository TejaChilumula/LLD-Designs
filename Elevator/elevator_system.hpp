#pragma once
#include <vector>
#include "elevator.hpp"
#include "scheduler.hpp"
#include "strategy.hpp"
#include "floor.hpp"  // Include Floor class

class ElevatorSystem {
    std::vector<Elevator*> elevators;
    Scheduler* scheduler;
    Strategy* strategy;  // Shared strategy instance
    std::vector<Floor> floors;

public:
    ElevatorSystem(int elevatorCount, int floorCount, Scheduler* sch, Strategy* strat)
        : scheduler(sch), strategy(strat) {
        
        // Create floors
        for (int i = 0; i < floorCount; ++i)
            floors.emplace_back(i);

        // Create elevators
        for (int i = 0; i < elevatorCount; ++i)
            elevators.push_back(new Elevator(i, strategy));
    }

    ~ElevatorSystem() {
        for (auto e : elevators) delete e;
        delete scheduler;
        delete strategy;
    }

    void addObserverToAll(ElevatorObserver* obs) {
        for (auto* e : elevators)
            e->addObserver(obs);
    }

    void handleRequest(const Request& req) {
        int assignedId = scheduler->assignElevator(elevators, req);
        if (assignedId != -1) {
            std::cout << "[System] Assigning floor " << req.floor.getNumber()
                      << " request to Elevator " << assignedId << std::endl;
            elevators[assignedId]->addRequest(req);
        } else {
            std::cout << "[System] No elevator available for floor "
                      << req.floor.getNumber() << std::endl;
        }
    }

    void stepAll() {
        for (auto* e : elevators)
            e->step();
    }

    std::vector<Elevator*> getElevatorPtrs() {
        return elevators;
    }

    Elevator* getElevatorById(int id) {
        for (auto& e : elevators) {
            if (e->getId() == id)
                return e;
        }
        return nullptr;
    }

    const std::vector<Floor>& getFloors() const {
        return floors;
    }
};
