// observer.hpp
#pragma once

enum class ElevatorState;

class ElevatorObserver {
public:
    virtual void onFloorChange(int elevatorId, int floor) = 0;
    virtual void onStateChange(int elevatorId, ElevatorState state) = 0;
    virtual ~ElevatorObserver() = default;
};
