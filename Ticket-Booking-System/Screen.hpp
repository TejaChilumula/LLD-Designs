#pragma once
#include "Show.hpp"
#include <unordered_map>
#include <memory>

class Screen {
    int screenId;
    std::unordered_map<int, std::shared_ptr<Show>> shows;

public:
    // ✅ Make sure this constructor is defined, not just declared
    Screen(int id) : screenId(id) {}

    void addShow(int showId, int seatCount) {
        shows[showId] = std::make_shared<Show>(showId, seatCount);
    }

    std::shared_ptr<Show> getShow(int showId) {
        if (shows.find(showId) != shows.end()) return shows[showId];
        return nullptr;
    }

    int getId() const { return screenId; }
};
