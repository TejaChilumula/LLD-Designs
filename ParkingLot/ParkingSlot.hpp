#ifndef PARKINGSLOT_HPP
#define PARKINGSLOT_HPP

#include "Vehicle.hpp"

class ParkingSlot {
    public:
        int id;
        int priority;
        VehicleType type;
        bool isOccupied;
        Vehicle* parkedVehicle;

        ParkingSlot(int id, VehicleType type, int priority = 100) : id(id), type(type), isOccupied(false), parkedVehicle(nullptr) {}

        bool canFit(VehicleType vehicleType){
            return static_cast<int>(type)>= static_cast<int>(vehicleType);
        }

        void parkVehicle(Vehicle* vehicle){
            parkedVehicle = vehicle;
            isOccupied = true;
        }

        void removeVehicle(){
            parkedVehicle = nullptr;
            isOccupied = false;
        }

};

#endif
