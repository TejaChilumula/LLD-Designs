#include <iostream>
#include "Gameboard.hpp"

int main() {
    int boardSize, numSnakes, numLadders, numPlayers, numDice;

    std::cout << "Enter board size (e.g., 100): ";
    std::cin >> boardSize;

    std::cout << "Enter number of snakes: ";
    std::cin >> numSnakes;

    std::cout << "Enter number of ladders: ";
    std::cin >> numLadders;

    std::cout << "Enter number of players: ";
    std::cin >> numPlayers;

    std::cout << "Enter number of dice: ";
    std::cin >> numDice;

    Gameboard game(boardSize, numDice, numPlayers);

    std::cout << "\nEnter snakes (start > end):" << std::endl;
    for (int i = 0; i < numSnakes; i++) {
        int start, end;
        std::cout << "Snake " << i + 1 << ": ";
        std::cin >> start >> end;

        if (start <= end || start > boardSize || end < 1) {
            std::cout << "Invalid snake. Try again." << std::endl;
            i--;
            continue;
        }

        game.addJump(Jump(start, end));
    }

    std::cout << "\nEnter ladders (start < end):" << std::endl;
    for (int i = 0; i < numLadders; i++) {
        int start, end;
        std::cout << "Ladder " << i + 1 << ": ";
        std::cin >> start >> end;

        if (start >= end || start < 1 || end > boardSize) {
            std::cout << "Invalid ladder. Try again." << std::endl;
            i--;
            continue;
        }

        game.addJump(Jump(start, end));
    }

    std::cout << "\nGame starting...\n" << std::endl;
    game.startGame();

    return 0;
}
