#pragma once
#include "elevator.hpp"

class Elevator; // Forward declaration


class Strategy{
    public:
        virtual int getNextStop(Elevator* elevator) = 0;
        virtual ~Strategy() = default;
};