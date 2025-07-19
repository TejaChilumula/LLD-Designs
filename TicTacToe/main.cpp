#include "TicTacToeBoard.hpp"
#include "HumanMoveStrategy.hpp"
#include "Player.hpp"
#include "GameObserver.hpp"

#include <iostream>
#include <memory>
#include <vector>

using namespace std;

// A simple console observer for debugging and event messages
class ConsoleObserver : public GameObserver {
public:
    void onMoveMade(int playerId, int row, int col) override {
        cout << "[Observer] Player " << playerId << " moved to (" << row << ", " << col << ")\n";
    }

    void onGameWon(int playerId, const string& playerName) override {
        cout << "\n🏆 " << playerName << " (Player " << playerId << ") wins the game!\n";
    }

    void onGameDraw() override {
        cout << "\n🤝 The game ended in a draw!\n";
    }
};

    int main() {
    int boardSize;
    cout << "Enter board size (e.g. 3 for 3x3): ";
    cin >> boardSize;

    // Create players with strategy (Human in this case)
    vector<Player*> players;
    players.push_back(new Player(1, "Player 1", new HumanMoveStrategy()));
    players.push_back(new Player(2, "Player 2", new HumanMoveStrategy()));

    // Create the game engine
    TicTacToeBoard game(boardSize, players);

    // Attach an observer
    game.addObserver(new ConsoleObserver());

    // Start the game
    game.startGame();

    // Clean up
    for (auto* p : players) delete p;
    return 0;
}