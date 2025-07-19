#pragma once

#include <string>

class GameObserver {
public:
    virtual void onMoveMade(int playerId, int row, int col) = 0;
    virtual void onGameWon(int winnerId, const std::string& winnerName) = 0;
    virtual void onGameDraw() = 0;

    virtual ~GameObserver() = default;
};
