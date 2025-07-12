#pragma once
#include "Screen.hpp"
#include<unordered_map>

class Theatre{
    int theatreId;
    unordered_map<int, shared_ptr<Screen>> screens;

public:
    Theatre(int id): theatreId(id) {}

    void addScreen(int screenId){
        screens[screenId] = make_shared<Screen>(screenId);
    }

    shared_ptr<Screen> getScreen(int screenId){
        if(screens.find(screenId) != screens.end()) return screens[screenId];
        return nullptr;
    }

    int getId() const{ return theatreId;}
};