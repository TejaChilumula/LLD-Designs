#pragma once

#include "MoveStrategy.hpp"
#include <iostream>
#include <limits>

using namespace std;

class HumanMoveStrategy : public MoveStrategy {
public:
    std::pair<int, int> getMove(int playerId, int boardSize) override {
        int row, col;

        while (true) {
            std::cout << "Player " << playerId << ", enter your move (row col): ";
            std::cin >> row >> col;

            // Handle bad input (e.g. letters, symbols)
            if (std::cin.fail()) {
                std::cin.clear(); // Clear error state
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard bad input
                std::cout << "Invalid input. Please enter two integers.\n";
                continue;
            }

            // Check if row and col are within board bounds
            if (row >= 0 && row < boardSize && col >= 0 && col < boardSize) {
                return {row, col}; // Valid move
            }

            std::cout << "Move out of bounds. Please enter values between 0 and " << boardSize - 1 << ".\n";
        }
    }

    std::string getName() const override {
        return "Human";
    }
};