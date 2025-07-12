#pragma once
#include "Show.hpp"
#include<unordered_map>

class Screen {
    int screenId;
    unordered_map<int, shared_ptr<Show>> shows;

public:
    Screen(int id) : screenId(id) {}

    void addShow(int showId, int seatCount){
        shows[showId] = make_shared<Show>(showId, seatCount);
    }

    shared_ptr<Show> getShow(int showId){
        if(shows.find(showId) != shows.end()) return shows[showId];
        return nullptr;
    }

    int getId() const { return screenId;}
};