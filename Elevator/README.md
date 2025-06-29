# Elevator System Simulation

## Overview
This project simulates an elevator control system with multiple elevators, handling external and internal requests to move between floors. It uses different scheduling and stopping strategies to decide elevator movements.

## Key Features
- **Elevator and Floor Classes:** Represents elevators and floors as objects.
- **Requests:** External (hall calls) and internal (inside elevator) requests handled.
- **Scheduling Strategies:** Assign elevators to requests optimally.
- **Stopping Strategies:** Decide next floor to stop for each elevator.
- **Observer Pattern:** Logs elevator floor changes and state updates.
- **Dynamic Internal Requests:** Simulates users entering elevator and choosing floors.

## Implemented Strategies
- **LOOK:** Elevator continues in current direction until no requests remain, then reverses.
- **FIFO:** First-come-first-serve stopping strategy.
- **SCAN:** Elevator moves in one direction serving all requests, then reverses.

## Design Patterns Used
- **Strategy Pattern:** For flexible scheduling and stopping logic.
- **Observer Pattern:** For logging elevator state and floor changes.

## How to Run
- Compile all `.cpp` files.
- Run the executable.
- The console shows elevator movements, stops, and state changes.

## Future Improvements
- Add GUI visualization.
- Improve scheduling with load balancing.
- Support more complex request types and priorities.
