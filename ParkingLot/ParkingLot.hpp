#ifndef PARKINGLOT_HPP
#define PARKINGLOT_HPP
#include "ParkingFloor.hpp"
#include "Ticket.hpp"
#include "PricingStrategy.hpp"
#include <map>
#include <iostream>

class ParkingLot {
private:
    std::map<int, ParkingFloor*> floors;
    PricingStrategy* strategy;

public:
    ParkingLot() : strategy(new FlatRateStrategy()) {}

    void setPricingStrategy(PricingStrategy* newStrategy){
        if(strategy) delete strategy;
        strategy = newStrategy;
    }

    void addFloor(ParkingFloor* floor){
        floors[floor->id] = floor;
    }

    Ticket* parkVehicle(Vehicle* vehicle){
        for(auto& [floorId, floor] : floors){
            ParkingSlot* slot = floor->findSlot(vehicle->type);
            if(slot){
                slot->parkVehicle(vehicle);
                return new Ticket(floorId, slot->id, vehicle->number);
            }
        }

        // If we wont find exact vehicle spot, we will give a spot which is in higher order to it bike  -> Car or Bike->Truck
        for(auto& [floorId, floor] : floors){
            ParkingSlot* slot = floor->findAnyFittingSlot(vehicle->type);
            if (slot) {
                slot->parkVehicle(vehicle);
                return new Ticket(floorId, slot->id, vehicle->number);
            }
        }

        std::cout<<"No slot found for"<<vehicle->number << std::endl;
        return nullptr;
    }


        void unparkVehicle(Ticket* ticket){
            ParkingFloor* floor = floors[ticket->floorId];
            ParkingSlot* slot = floor->slots[ticket->slotId];
            slot->removeVehicle();

            auto duration = std::chrono::duration_cast<std::chrono::minutes>(
                std::chrono::system_clock::now() - ticket->entryTime).count(); // count extracts the actual numeric value ( in this case no of minutes as long long pr int64_t)
             
            double price = strategy->calculate(duration);
            ticket->isPaid = true;

        std::cout << "Vehicle " << ticket->vehicleNumber << " unparked. Fee: $." << price << "\n";
        }

        //Destructor
        ~ParkingLot() {
        delete strategy;
        }
    };
    #endif