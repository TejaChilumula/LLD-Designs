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
    thread cleanerThread;

public:

    BookingManager bookingManager;

    TicketBookingSystem(){
        cleanerThread = thread([this]() { this->startCleaner(); });

    }

    ~TicketBookingSystem(){
    { lock_guard<mutex> lock(systemMutex);
        stopCleaner = true;
    }

    if(cleanerThread.joinable()) cleanerThread.join();
    }

    BookingManager& getBookingManager() {
    return bookingManager;
    }

    void addTheatre(int theatreId) {
        lock_guard<mutex> lock(systemMutex);
        theatres[theatreId] = make_shared<Theatre>(theatreId);
    }

    // To Add Screens to the existing theatres Theatres
    void addScreenToTheatre(int theatreId, int screenId){
        lock_guard<mutex> lock(systemMutex);
        if(theatres.find(theatreId) != theatres.end()){
            theatres[theatreId]->addScreen(screenId);
        }
    }

    // To Add Show to the existing Theatre and Screen
    void addShow(int theatreId, int screenId, int showId, int seatCount){
        lock_guard<mutex> lock(systemMutex);
        if(theatres.find(theatreId) != theatres.end()){
            auto screen = theatres[theatreId]->getScreen(screenId);
            if(screen)
                screen->addShow(showId, seatCount);
        }
    }

    // To hold the seats, if even one seat is also not available
    // We return false !!!
bool holdSeats(int userId, int theatreId, int screenId, int showId, const std::vector<int>& seatIds) {
    std::shared_ptr<Show> show = getShow(theatreId, screenId, showId);
    if (!show) return false;

    auto seats = show->getSeats(seatIds);
    sort(seats.begin(), seats.end(), [](const auto& a, const auto& b) {
        return a->getId() < b->getId();
    });

    std::vector<shared_ptr<Seat>> heldNow;

    for (auto& seat : seats) {
        if (seat->tryHold(userId)) {
            heldNow.push_back(seat);
        } else {
            // rollback only the ones held during this call
            for (auto& s : heldNow)
                s->cancelHoldorBooking(userId);
            return false;
        }
    }

    return true;
}


std::shared_ptr<Booking> confirmBooking(int userId, int theatreId, int screenId, int showId, const std::vector<int>& seatIds) {
    std::shared_ptr<Show> show = getShow(theatreId, screenId, showId);
    if (!show) return nullptr;

    auto seats = show->getSeats(seatIds);
    std::sort(seats.begin(), seats.end(), [](const auto& a, const auto& b) {
        return a->getId() < b->getId();
    });

    std::vector<Seat*> confirmed;
    for (auto& seat : seats) {
        if (seat->confirmBooking(userId)) {
            confirmed.push_back(seat.get());
        } else {
            for (auto* s : confirmed) s->cancelHoldorBooking(userId);
            return nullptr;
        }
    }

    return bookingManager.createBooking(userId, theatreId, screenId, showId, seatIds);
}



    private:
        std::shared_ptr<Show> getShow(int theatreId, int screenId, int showId) {
            std::lock_guard<std::mutex> lock(systemMutex);
            if (theatres.find(theatreId) != theatres.end()) {
                auto screen = theatres[theatreId]->getScreen(screenId);
                if (screen) return screen->getShow(showId);
            }
            return nullptr;
        }


        void startCleaner(){
            while(true){

                this_thread::sleep_for(chrono::seconds(30));
                lock_guard<mutex> lock(systemMutex);
                if(stopCleaner) break;

                for(auto& [tid, theatre] : theatres){
                    for(int sid = 0; sid < 100; ++sid){
                        auto screen = theatre->getScreen(sid);
                        if(!screen) continue;
                        

                        for(int shid = 0; shid < 100; ++shid){
                            auto show = screen->getShow(shid);
                            if(!show) continue;

                            for(int i=0;i<100;++i){
                                auto seat = show->getSeat(i);
                                if(seat) seat->checkHoldExpired();
                            }
                        }
                    }
                }
            }
        }

};