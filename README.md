# 🐞 A Bug's Life

*A Bug’s Life* is a C++ simulation that brings a bug-filled battlefield to life on a 10x10 grid. Each bug has its own behavior, and when the board is “Tapped” (shaken), they move — and may fight to the death if they collide. The biggest bug survives. The simulation continues until only one bug remains standing.

---

## 📦 Project Stages

### ✅ Stage 1 – Basic Bug Simulation (Console-Based)

This initial version provides a working simulation engine and a basic text interface for interaction. All bugs are manually defined and move according to their unique logic. When two or more bugs occupy the same cell, the largest eats the others.

#### 🎯 Key Features – Stage 1
- 10x10 grid-based **Bug Board**
- Core bug movement and fight logic
- “Tap” feature to trigger movement
- End condition: only one bug left
- Simple console interaction and bug output

#### 📋 Sample Menu (Stage 1)
> Limited interaction via function calls and hardcoded bug initialization.

---

### 🚀 Stage 2 – Enhanced Simulation with Inheritance & Menu System

Building on Stage 1, Stage 2 introduces an **abstract class (`Bug`)**, supports multiple bug types through inheritance, and provides a full **console menu interface**. Bug life history is now tracked, and data is read/written from/to files.

#### 🧠 Object-Oriented Design
- **Abstract Class: `Bug`**
    - Attributes: ID, position, direction, size, alive status, path history
    - Pure virtual function: `move()`
    - Shared methods: `fight()`, `isWayBlocked()`, etc.
- **Derived Bug Types:**
    - `Crawler`, `Hopper`, `Jumper`
    - Each with distinct movement logic

#### 📋 Console Menu (Stage 2)
1. Initialize Bug Board (load data from file)
2. Display all Bugs
3. Find a Bug (given an id)
4. Tap the Bug Board (cause all to move, then fight/eat)
5. Display Life History of all Bugs (path taken)
6. Display all Cells listing their Bugs
7. Run simulation (generates a Tap every second)
8. Exit (write Life History of all Bugs to file)

---

## 🧪 How to Run the Project

### ✅ Requirements
- C++17 or later
- CMake (if using CLion or SFML)
- Terminal / CLion / VSCode
- [Optional] SFML (for GUI version of Stage 2)
---

## 📄 Bug Data File Format – `bugs.txt`

The `bugs.txt` file is used to **initialize the Bug Board**. Each line in the file represents a single bug, using a comma-separated format.

### 🔢 Format

```plaintext
<Type>,<ID>,<X>,<Y>,<Direction>,<Size>
```
## 👥 Authors
•	Luke Kirwan \
•	Eyob