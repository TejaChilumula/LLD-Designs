#pragma once
#include <mutex>
#include <chrono>
#include <iostream>

class Seat {
    int seatId;
    bool isBooked = false;
    bool isHeld = false;
    int heldByUserId = -1;
    std::chrono::steady_clock::time_point holdStartTime;
    std::mutex seatMutex;
    const int holdDurationSec = 60;

public:
    Seat(int id) : seatId(id) {}

    bool tryHold(int userId) {
        std::lock_guard<std::mutex> lock(seatMutex);
        if (isBooked || isHeld) return false;
        isHeld = true;
        heldByUserId = userId;
        holdStartTime = std::chrono::steady_clock::now();
        std::cout << "[Seat " << seatId << "] held by User " << userId << "\n";
        return true;
    }

    bool confirmBooking(int userId) {
        std::lock_guard<std::mutex> lock(seatMutex);
        if (!isHeld || heldByUserId != userId) {
            std::cout << "[Seat " << seatId << "] confirm failed (held=" << isHeld << ", heldBy=" << heldByUserId << ", requester=" << userId << ")\n";
            return false;
        }
        isHeld = false;
        isBooked = true;
        heldByUserId = -1;
        std::cout << "[Seat " << seatId << "] booked by User " << userId << "\n";
        return true;
    }

    bool cancelHoldorBooking(int userId){
    std::lock_guard<std::mutex> lock(seatMutex);
    if (isHeld && heldByUserId == userId) {
        std::cout << "[Seat " << seatId << "] hold cancelled (user=" << userId << ")\n";
        isHeld = false;
        heldByUserId = -1;
        return true;
    }
    return false;
}


    bool checkHoldExpired() {
        std::lock_guard<std::mutex> lock(seatMutex);
        if (isHeld && std::chrono::steady_clock::now() - holdStartTime > std::chrono::seconds(holdDurationSec)) {
            std::cout << "[Seat " << seatId << "] hold expired (user=" << heldByUserId << ")\n";
            isHeld = false;
            heldByUserId = -1;
            return true;
        }
        return false;
    }

    int getId() const { return seatId; }
    bool booked() const { return isBooked; }
    bool held() const { return isHeld; }
    int getHeldBy() const { return heldByUserId; }
};
