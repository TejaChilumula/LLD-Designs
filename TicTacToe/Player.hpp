#pragma once

#include "MoveStrategy.hpp"
#include <string>

class Player{
    public:
        int id;
        string name;
        MoveStrategy* strategy;
    
    public:
        Player(int _id, const std::string& _name, MoveStrategy* _strategy)
            : id(_id), name(_name), strategy(_strategy) {}

        int getId() const { return id; }
        std::string getName() const { return name; }

        std::pair<int, int> getMove(int boardSize) {
            return strategy->getMove(id, boardSize);
        }
};