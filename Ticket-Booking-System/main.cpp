#include "TicketBookingSystem.hpp"
#include "BookingManager.hpp"
#include "User.hpp"
#include <thread>
#include <chrono>
#include <iostream>

// Simulates seat booking from a user thread
void bookSeatsThread(TicketBookingSystem& system, const User& user, int theatreId, int screenId, int showId, const std::vector<int>& seatIds) {
    std::cout << user.getName() << " is trying to book seats: ";
    for (int s : seatIds) std::cout << s << " ";
    std::cout << "\n";

    if (system.holdSeats(user.getId(), theatreId, screenId, showId, seatIds)) {
        std::cout << user.getName() << " held seats successfully. Processing payment...\n";
        std::this_thread::sleep_for(std::chrono::seconds(2)); // simulate payment delay

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

int main() {
    TicketBookingSystem system;

    // Setup
    int theatreId = 1, screenId = 1, showId = 101;
    system.addTheatre(theatreId);
    system.addScreenToTheatre(theatreId, screenId);
    system.addShow(theatreId, screenId, showId, 10);  // total 10 seats: 0-9

    // Users
    User alice(1, "Alice");
    User bob(2, "Bob");

    // Seat preferences
    std::vector<int> aliceSeats = {3, 4, 5};
    std::vector<int> bobSeats   = {4, 5, 6};

    // Booking threads
    std::thread t1(bookSeatsThread, std::ref(system), std::ref(alice), theatreId, screenId, showId, aliceSeats);
    std::thread t2(bookSeatsThread, std::ref(system), std::ref(bob), theatreId, screenId, showId, bobSeats);

    t1.join();
    t2.join();

    // Final booking status
    std::cout << "\n📒 Alice's bookings:\n";
    system.getBookingManager().printBookingsForUser(alice.getId());

    std::cout << "\n📒 Bob's bookings:\n";
    system.getBookingManager().printBookingsForUser(bob.getId());

    return 0;
}
