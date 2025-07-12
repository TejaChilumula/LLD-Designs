#pragma once
#include "Booking.hpp"
#include <unordered_map>
#include <memory>

using namespace std;

class BookingManager {
    std::unordered_map<int, std::vector<std::shared_ptr<Booking>>> userBookings;
    std::unordered_map<std::string, std::shared_ptr<Booking>> qrMap;
    int nextBookingId = 1;

public:
    shared_ptr<Booking> createBooking(int userId, int theatreId, 
        int screenId, int showId, const std::vector<int>& seats) {
            auto booking = make_shared<Booking>(nextBookingId++, userId, theatreId, screenId, showId, seats);
            userBookings[userId].push_back(booking);
            qrMap[booking->getQR()] = booking;
            return booking;
        }

    vector<std::shared_ptr<Booking>> getBookingsForUser(int userId) {
        return userBookings[userId];  // returns empty if user has no bookings
    }
    
    
    shared_ptr<Booking> getBookingByQR(const string& qr){
        return qrMap.count(qr) ? qrMap[qr] : nullptr;
    }
    
    void printBookingsForUser(int userId) {
        if (userBookings.find(userId) == userBookings.end()) {
            std::cout << "No bookings found for user " << userId << "\n";
            return;
        }
        for (const auto& b : userBookings[userId]) {
            std::cout << "Booking ID: " << b->getBookingId()
                    << ", Theatre: " << b->getTheatreId()
                    << ", Screen: " << b->getScreenId()
                    << ", Show: " << b->getShowId()
                    << ", Seats: ";
            for (int sid : b->getSeatIds()) std::cout << sid << " ";
            std::cout << "\n";
        }
    }


};