#pragma once
#include "Screen.hpp"
#include <unordered_map>
#include <memory>

class Theatre {
    int theatreId;
    std::unordered_map<int, std::shared_ptr<Screen>> screens;

public:
    Theatre(int id) : theatreId(id) {} // ✅ required for make_shared<Theatre>(int)

    void addScreen(int screenId) {
        screens[screenId] = std::make_shared<Screen>(screenId);
    }

    std::shared_ptr<Screen> getScreen(int screenId) {
        if (screens.count(screenId)) return screens[screenId];
        return nullptr;
    }

    int getId() const { return theatreId; }
};
