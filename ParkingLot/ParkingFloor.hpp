#ifndef PARKINGFLOOR_HPP
#define PARKINGFLOOR_HPP
#include "ParkingSlot.hpp"
#include <vector>
#include <algorithm>

class ParkingFloor {

    public:
        int id;
        std::vector<ParkingSlot*> slots;

        ParkingFloor(int id) : id(id) {}

        void addSlot(ParkingSlot* slot){
            slots.push_back(slot);
        }

        ParkingSlot* findSlot(VehicleType vType){
            // if incase you want any priority slot
            ParkingSlot* bestSlot = nullptr;
            for(auto& slot : slots)
                if(!slot->isOccupied && slot->type == vType) return bestSlot = slot; 
            
            return bestSlot;
            }



        ParkingSlot* findAnyFittingSlot(VehicleType vType){
            ParkingSlot* bestSlot = nullptr;
            for(auto& slot : slots)
                if(!slot->isOccupied && slot->canFit(vType)) return  bestSlot = slot; 
            return bestSlot;
        }



};
#endif
