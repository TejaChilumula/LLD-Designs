#ifndef TICKET_HPP
#define TICKET_HPP
#include <iostream>
#include <string>
#include <chrono>
#include <sstream>
#include <iomanip>


class Ticket{

    std::string generateTicketId(){
        // Generate ticket ID based on current time + floor + slot 
        auto now = std::chrono::system_clock::now();
        std::time_t now_c = std::chrono::system_clock::to_time_t(now);
        
        std::stringstream ss;
        // Format: YYYYMMDDHHMMSS_F{floorId}_S{slotId}_C{counter}
        ss << std::put_time(std::localtime(&now_c), "%Y%m%d%H%M%S");
        ss << "_F" << floorId << "_S" << slotId ;
        return ss.str();
    }

public:
    std:: string ticketId;
    int floorId;
    int slotId;
    std::string vehicleNumber;
    std::chrono::system_clock::time_point entryTime;
    bool isPaid;

    Ticket(int f, int s, const std::string& num) : floorId(f), slotId(s), vehicleNumber(num), entryTime(std::chrono::system_clock::now()), isPaid(false)
    {
        ticketId = generateTicketId();
    }

    std::string getTicketId() const {
        return ticketId;
    }

};
#endif