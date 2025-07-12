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

bool holdSeats(int theatreId, int screenId, int showId, const std::vector<int>& seatIds) {
    std::shared_ptr<Show> show = getShow(theatreId, screenId, showId);
    if (!show) return false;

    auto seats = show->getSeats(seatIds);
    sort(seats.begin(), seats.end(), [](const auto&a, const auto&b){
        return a->getId < b->getId();
    });

    for(auto& seat : seats){
        // This is for the multiple seats booking, if any of the seat booked, then we make all the
        // seats available and cancel the order.
        if(!seat->tryHold()){
            for(auto& s : seats) s->cancelHoldorBooking();
            return false;
        }
        return true;
    }

shared_ptr<Booking> confirmBooking(int userId, int theatreId, int screenId, int showId, const std::vector<int>& seatIds) {
        std::shared_ptr<Show> show = getShow(theatreId, screenId, showId);
        if(!show) return nullptr;

        auto seats = show->getSeats(seatIds);
        for(auto& seat : seats){
            if(!seat->confirmBooking()) return nullptr;
        }

        return bookingManager.createBooking(userId, theatreId, screenId, showId, seatIds );
        