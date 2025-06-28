// PlayerFactory.hpp
#ifndef PLAYER_FACTORY_HPP
#define PLAYER_FACTORY_HPP

#include "Player.hpp"
#include <vector>
#include <string>
#include <iostream>

class PlayerFactory {
public:
    static std::vector<Player> createPlayers(int count) {
        std::vector<Player> players;
        for (int i = 0; i < count; ++i) {
            std::string name;
            std::cout << "Enter name for player " << (i + 1) << ": ";
            std::cin >> name;
            players.emplace_back(name);
        }
        return players;
    }
};

#endif
