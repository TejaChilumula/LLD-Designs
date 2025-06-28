// main.cpp
#include "ParkingLot.hpp"
#include "Vehicle.hpp"
#include "PricingStrategy.hpp"

#include<chrono>

int main() {
    ParkingLot lot;
    lot.setPricingStrategy(new HourlyRateStrategy());

    auto* floor1 = new ParkingFloor(1);
    floor1->addSlot(new ParkingSlot(0, VehicleType::CAR, 1));
    floor1->addSlot(new ParkingSlot(1, VehicleType::CAR, 2));
    lot.addFloor(floor1);

    Vehicle* car = new Vehicle(VehicleType::CAR, "TS09AB1234");
    Ticket* ticket = lot.parkVehicle(car);

    if (ticket) {
        std::cout << "Ticket generated. Vehicle: " << ticket->vehicleNumber << "\n";
        std::cout << "Ticket" << "\n"
                  << "Ticket ID: " << ticket->getTicketId() << "\n"
                  << "Parking Start-Time: " 
                  << 
                        std::chrono::system_clock::to_time_t(ticket->entryTime);
        lot.unparkVehicle(ticket);
    }

    // Manual cleanup
    delete car;
    delete ticket;
    for (auto slot : floor1->slots) delete slot;
    delete floor1;

    return 0;
}
