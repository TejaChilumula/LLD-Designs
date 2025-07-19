#pragma once

#include "GameBoard.hpp"
#include "Player.hpp"
#include "GameObserver.hpp"
#include <vector>
#include <memory>


using namespace std;

class TicTacToeBoard {
private:
    GameBoard board;
    vector<Player*> players;
    vector<GameObserver*> observers;

    int currentPlayerIdx;

public:
    TicTacToeBoard(int _boardSize, const vector<Player*>& _players):
        board(_boardSize), players(_players), currentPlayerIdx(0) {}
    
    void addObserver(GameObserver* observer){
        observers.push_back(observer);
        }
    
    void notifyMove(int playerId, int row, int col){
        for(auto* obs : observers)
            obs->onMoveMade(playerId,row, col);
    }

    
    void notifyWin(int playerId, const std::string& name) {
        for (auto* obs : observers) {
            obs->onGameWon(playerId, name);
        }
    }

    void notifyDraw() {
        for (auto* obs : observers) {
            obs->onGameDraw();
        }
    }

    void startGame() {
    board.reset();

    while (true) {
        Player* currentPlayer = players[currentPlayerIdx];
        int playerId = currentPlayer->getId();
        const std::string& playerName = currentPlayer->getName();

        std::cout << "\n" << playerName << "'s turn...\n";

        auto [row, col] = currentPlayer->getMove(board.getSize());

        if (!board.makeMove(row, col, playerId)) {
            std::cout << "Invalid move. Cell already occupied or out of bounds.\n";
            continue;
        }

        notifyMove(playerId, row, col);
        board.printBoard(); // or board.display();

        GameState state = board.checkGameState(row, col, playerId);

        if (state == GameState::WIN) {
            notifyWin(playerId, playerName);
            break;
        } else if (state == GameState::DRAW) {
            notifyDraw();
            break;
        }

        // Move to next player
        currentPlayerIdx = (currentPlayerIdx + 1) % players.size();
    }
}

};
    