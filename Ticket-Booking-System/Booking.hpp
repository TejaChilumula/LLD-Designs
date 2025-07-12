#pragma once
#include<vector>
#include<string>
#include<chrono>
#include<iostream>

using namespace std;

class Booking{
    int bookingId;
    int userId;
    int theatreId, screenId, showId;
    vector<int> seatIds;
    string qrToken;
    chrono::system_clock::time_point bookingTime;

public:
    Booking(int _bookingId, int _userId, int _theatreId, 
    int _screenId, int _showId, const vector<int>& _seats):
    bookingId(_bookingId), userId(_userId),
    theatreId(_theatreId),
    screenId(_screenId), showId(showId),
    seatIds(_seats), bookingTime(chrono::system_clock::now()){
        qrToken = generateToken();
    };

    string generateToken(){
        return "QR-"+to_string(bookingId)+"-"
        +to_string(std::chrono::system_clock::now().time_since_epoch().count());
    }

    int getUserId() const { return userId;}
    string getQR() const { return qrToken; }
    int getBookingId() const { return bookingId;}
    vector<int> getSeatIds() const { return seatIds;}

    void print() const;
};


inline void Booking::print() const{
    cout << "Booking #" << bookingId << " by User " << userId
              << " [Show: " << showId << ", Seats: ";
    for (int id : seatIds) cout << id << " ";
    cout << "] QR: " << qrToken << "\n";
}
