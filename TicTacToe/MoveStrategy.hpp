#pragma once

#include<utility>
#include<string>


using namespace std;
class MoveStrategy{
    public:
        virtual pair<int, int> getMove(int playerId, int boardSize) = 0;
        virtual string getName() const = 0;
        virtual ~MoveStrategy() {}
};