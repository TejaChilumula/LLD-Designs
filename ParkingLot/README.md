Parking Lot System - C++ (LLD Project)

This is a **Low-Level Design (LLD)** implementation of a multi-floor parking lot system using **C++** with manual memory management (no smart pointers).

It supports:
- Multiple floors and slots
- Different vehicle types (bike, car, truck)
- Nearest slot selection using priority

## ✅ Features

- 🏢 **Multi-floor support**  
- 🅿️ **Slot assignment based on vehicle type and priority**  
- 🎟 **Ticket generation on entry**  
- 💳 **Payment calculation based on duration**
- 🧠 **Strategy Pattern** for pricing logic  
- 👨‍💻 Implemented using pure C++ and header files only

## 🧩 Design Patterns Used

| Pattern             | Description |
|---------------------|-------------|
| **Strategy Pattern** | Used for pricing logic. You can easily switch between Flat Rate or Hourly Rate strategies by injecting a different strategy class. |
| **Composition**      | A ParkingLot is composed of ParkingFloors, which are composed of ParkingSlots. |
| **Encapsulation**    | Each class handles its own logic (e.g., `ParkingSlot` tracks its own state). |

---


### 1. Compile:

```bash
g++ -std=c++17 main.cpp -o parking_lot

### 2. Run
    ./parking_lot


