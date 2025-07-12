#pragma once

#include "Theatre.hpp"
#include "BookingManager.hpp"

#include <mutex>
#include <thread>
#include <unordered_map>
#include <condition_variable>
#include <memory>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;

class TicketBookingSystem {
    std::unordered_map<int, std::shared_ptr<Theatre>> theatres;
    std::mutex systemMutex;
    bool stopCleaner = false;
    std::thread cleanerThread;

public:

    BookingManager bookingManager;

    TicketBookingSystem(){
        cleanerThread = thread(&TicketBookingSystem::startCleaner, this);
    }

    ~TicketBookingSystem(){
    { lock_guard<mutex> lock(systemMutex);
        stopCleaner = true;
    }

    if(cleanerThread.joinable()) cleanerThread.join();
    }

void addTheatre(int theatreId) {
    lock_guard<mutex> lock(systemMutex);
    theatres[theatreId] = make_shared<Theatre>(theatreId);
}

void addScreenToTheatre(int theatreId, int screenId){
    lock_guard<mutex> lock(systemMutex);
    if(theatres.find(theatreId) != theatres.end()){
        theatres[theatreId]->addScreen(screenId);
    }
}

void addShow(int theatreId, int screenId, int showId, int seatCount){
    lock_guard<mutex> lock(systemMutex);
    if(theatres.find(theatreId) != theatres.end()){
        auto screen = theatres[theatreId]->getScreen(screenId);
        if(screen)
            screen->addShow(showId, seatCount);
    }
}