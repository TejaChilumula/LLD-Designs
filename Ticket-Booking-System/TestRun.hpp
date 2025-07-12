#pragma once

#include "TicketBookingSystem.hpp"
#include "User.hpp"
#include <thread>
#include <chrono>
#include <vector>
#include <iostream>
#include <functional>

void simulateBooking(TicketBookingSystem& system, const User& user,
                     int theatreId, int screenId, int showId,
                     const std::vector<int>& seatIds, int delaySec = 0) {
    std::this_thread::sleep_for(std::chrono::seconds(delaySec));
    std::cout << user.getName() << " is trying to book seats: ";
    for (int s : seatIds) std::cout << s << " ";
    std::cout << "\n";

    if (system.holdSeats(user.getId(), theatreId, screenId, showId, seatIds)) {
        std::cout << user.getName() << " held seats successfully. Processing payment...\n";
        std::this_thread::sleep_for(std::chrono::seconds(2));

        auto booking = system.confirmBooking(user.getId(), theatreId, screenId, showId, seatIds);
        if (booking) {
            std::cout << "✅ " << user.getName() << "'s booking confirmed.\n";
            booking->print();
        } else {
            std::cout << "❌ " << user.getName() << "'s booking failed during confirmation.\n";
        }
    } else {
        std::cout << "❌ " << user.getName() << " couldn't hold the requested seats.\n";
    }
}

void runAllTests() {
    TicketBookingSystem system;

    int theatreId = 1, screenId = 1, showId = 101;
    system.addTheatre(theatreId);
    system.addScreenToTheatre(theatreId, screenId);
    system.addShow(theatreId, screenId, showId, 10); // 10 seats

    User u1(1, "Alice");
    User u2(2, "Bob");
    User u3(3, "Charlie");

    std::vector<int> seats1 = {3, 4, 5};
    std::vector<int> seats2 = {4, 5, 6};
    std::vector<int> seats3 = {7, 8};

    std::thread t1(simulateBooking, std::ref(system), std::ref(u1), theatreId, screenId, showId, seats1, 0);
    std::thread t2(simulateBooking, std::ref(system), std::ref(u2), theatreId, screenId, showId, seats2, 1);
    std::thread t3(simulateBooking, std::ref(system), std::ref(u3), theatreId, screenId, showId, seats3, 2);

    t1.join();
    t2.join();
    t3.join();

    std::cout << "\n📒 Alice's bookings:\n";
    system.getBookingManager().printBookingsForUser(u1.getId());

    std::cout << "\n📒 Bob's bookings:\n";
    system.getBookingManager().printBookingsForUser(u2.getId());

    std::cout << "\n📒 Charlie's bookings:\n";
    system.getBookingManager().printBookingsForUser(u3.getId());
}
