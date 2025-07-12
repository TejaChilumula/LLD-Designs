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

