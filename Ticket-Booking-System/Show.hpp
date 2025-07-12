#pragma once
#include "Seat.hpp"
#include <vector>
#include <memory>

class Show {
    int showId;
    std::vector<std::shared_ptr<Seat>> seats;

public:
    // ✅ Public constructor with proper parameter types
    Show(int id, int seatCount) : showId(id) {
        for (int i = 0; i < seatCount; ++i)
            seats.push_back(std::make_shared<Seat>(i));
    }

    std::shared_ptr<Seat> getSeat(int seatId) {
        if (seatId >= 0 && seatId < seats.size()) return seats[seatId];
        return nullptr;
    }

    std::vector<std::shared_ptr<Seat>> getSeats(const std::vector<int>& seatIds) {
        std::vector<std::shared_ptr<Seat>> result;
        for (int id : seatIds) {
            auto seat = getSeat(id);
            if (!seat) return {};
            result.push_back(seat);
        }
        return result;
    }

    int getId() const { return showId; }
};
