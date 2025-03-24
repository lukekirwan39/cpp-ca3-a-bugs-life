# 🐞 A Bug's Life - Stage 1

**CA3 - Stage 1 (2%)**  
**Semester 2 – 2024-2025**  
**B.Sc. (Hons) in Computing in Games Development / Software Development, Year 2**

---

## 📋 Overview

*A Bug’s Life* is a C++ console application that simulates the movement and interaction of various bugs on a 10x10 Bug Board. When the board is “Tapped” (shaken), each bug moves according to its behavior. If multiple bugs land on the same cell, they fight — and the biggest bug eats the rest. The game ends when only one bug remains.

This project represents **Stage 1** of the assignment and includes a **console-based interface** with a basic simulation engine.

---

## 👥 Authors

- **Luke Kirwan**
- **Eyob [Last Name]** *(Replace with Eyob’s surname)*

---

## 🎯 Features (Stage 1)

- 10x10 grid-based Bug Board
- Bug types with individual behaviors
- Movement logic triggered by a “Tap”
- Bug fighting and elimination
- End condition: one bug remains
- Console-based menu system

---

## 🧪 How to Run the Project

### Requirements
- A C++17+ compatible compiler (e.g. g++, clang++)
- A terminal or IDE like CLion / Visual Studio / Code::Blocks

### Compilation (CLI Example)
```bash
g++ -std=c++17 -o bugslife main.cpp
./bugslife
