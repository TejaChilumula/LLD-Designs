#include "TicketBookingSystem.hpp"
#include "BookingManager.hpp"
#include "User.hpp"
#include "TestRun.hpp"
#include <thread>
#include <chrono>
#include <iostream>


int main() {
    TicketBookingSystem system;

    runAllTests();

    return 0;
}
