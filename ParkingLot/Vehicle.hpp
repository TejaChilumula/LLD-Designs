#ifndef VEHICLE_HPP
#define VEHICLE_HPP
#include <string>

enum class VehicleType { BIKE, CAR, TRUCK};

class Vehicle {
    public:
     VehicleType type;
     std:: string number;
     Vehicle(VehicleType t, const std::string& num) : type(t), number(num) {} // smart constructor
};

#endif