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
    screenId(_screenId), showId(_showId),
    seatIds(_seats), bookingTime(chrono::system_clock::now()){
        qrToken = generateToken();
    };

    string generateToken(){
        return "QR-"+to_string(bookingId)+"-"
        +to_string(std::chrono::system_clock::now().time_since_epoch().count());
    }

    int getBookingId() const { return bookingId; }
    int getUserId() const { return userId; }
    int getTheatreId() const { return theatreId; }
    int getScreenId() const { return screenId; }
    int getShowId() const { return showId; }  // ✅ This line fixes your error
    const std::vector<int>& getSeatIds() const { return seatIds; }
    const std::string& getQR() const { return qrToken; }

    void print() const;
};


inline void Booking::print() const{
    cout << "Booking #" << bookingId << " by User " << userId
              << " [Show: " << showId << ", Seats: ";
    for (int id : seatIds) cout << id << " ";
    cout << "] QR: " << qrToken << "\n";
}
