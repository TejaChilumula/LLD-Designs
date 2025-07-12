#pragma once
#include<mutex>
#include<chrono>
using namespace std;

class Seat{
    int seatId;
    bool isBooked = false;
    bool isHeld = false;
    chrono::steady_clock::time_point holdStartTime;
    mutex seatMutex;
    int holdDurationSec = 10;

public:
    Seat(int id) : seatId(id) {}

    bool tryHold(){
        lock_guard<mutex> loc(seatMutex);
        if(isBooked || isHeld) return false;
        isHeld = true;
        holdStartTime = chrono::steady_clock::now();
        return true;
    }

    bool confirmBooking(){
        lock_guard<mutex> loc(seatMutex);

        if(!isHeld) return false;
        isHeld = false;
        isBooked = true;
        return true;
    }

    bool cancelHoldorBooking(){
        lock_guard<mutex> lock(seatMutex);
        if(isHeld) { isHeld = false; return true;}
        if(isBooked){isBooked = false; return true;}
        return false;
    }

    bool checkHoldExpired(){
        lock_guard<mutex> lock(seatMutex);
        if(isHeld && chrono::steady_clock::now() - holdStartTime > std::chrono::seconds(holdDurationSec)){
            isHeld = false;
            return true;
        }
        return false;
    }

    int getId() const { return seatId;}
    bool booked() const {return isBooked;}
    bool held() const { return isHeld;}
};