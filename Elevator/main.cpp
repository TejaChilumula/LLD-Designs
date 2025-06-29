#include "elevator_system.hpp"
#include "lookstrategy.hpp"
#include "floor.hpp"  // Include Floor class
#include <memory>
#include <thread>
#include <chrono>
#include <unordered_set>

class ConsoleLogger : public ElevatorObserver {
public:
    void onFloorChange(int elevatorId, int floor) override {
        std::cout << "[Logger] Elevator " << elevatorId << " at floor " << floor << std::endl;
    }
    void onStateChange(int elevatorId, ElevatorState state) override {
        std::cout << "[Logger] Elevator " << elevatorId << " changed state to ";
        switch (state) {
            case ElevatorState::IDLE: std::cout << "IDLE"; break;
            case ElevatorState::MOVING: std::cout << "MOVING"; break;
            case ElevatorState::STOPPED: std::cout << "STOPPED"; break;
            case ElevatorState::MAINTENANCE: std::cout << "MAINTENANCE"; break;
        }
        std::cout << std::endl;
    }
};

std::unordered_set<std::string> injected;

void injectInternalOnPickup(ElevatorSystem& system, int elevatorId, int pickupFloorNo, int internalFloorNo) {
    Elevator* e = system.getElevatorById(elevatorId);
    std::string key = std::to_string(elevatorId) + "_" + std::to_string(pickupFloorNo);
    if (e && e->isAtFloor(pickupFloorNo) && !injected.count(key)) {
        Floor internalFloor(internalFloorNo);
        Direction dir = (internalFloorNo > pickupFloorNo) ? Direction::UP : Direction::DOWN;
        Request internalRequest(internalFloor, dir, RequestType::INTERNAL);

        e->addRequest(internalRequest);
        std::cout << "[Simulation] User inside Elevator " << elevatorId << " pressed " << internalFloorNo << std::endl;
        injected.insert(key);
    }
}

int main() {
    Scheduler* scheduler = new LookScheduler();
    Strategy* strategy = new LookStrategy();
    ElevatorSystem system(3, 8, scheduler, strategy);

    ConsoleLogger logger;
    system.addObserverToAll(&logger);

    // External Requests with Floor object
    system.handleRequest(Request(Floor(3), Direction::UP, RequestType::EXTERNAL));
    system.handleRequest(Request(Floor(5), Direction::DOWN, RequestType::EXTERNAL));
    system.handleRequest(Request(Floor(1), Direction::UP, RequestType::EXTERNAL));
    system.handleRequest(Request(Floor(6), Direction::DOWN, RequestType::EXTERNAL));
    system.handleRequest(Request(Floor(2), Direction::UP, RequestType::EXTERNAL));

    // Simulation loop
    for (int i = 0; i < 30; ++i) {
        system.stepAll();

        injectInternalOnPickup(system, 0, 3, 7);
        injectInternalOnPickup(system, 0, 1, 4);
        injectInternalOnPickup(system, 0, 2, 8);
        injectInternalOnPickup(system, 1, 5, 1);
        injectInternalOnPickup(system, 2, 6, 2);

        std::this_thread::sleep_for(std::chrono::milliseconds(400));
    }

    return 0;
}
