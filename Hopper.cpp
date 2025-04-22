#include "Hopper.h"
#include <iostream>
#include <cstdlib>

void Hopper::move() {
    if (!isAlive()) return;

    const int boardWidth = 10;
    const int boardHeight = 10;

    int dx = 0, dy = 0;

    direction = static_cast<Direction>(1 + rand() % 4);

    switch (direction) {
    case Direction::NORTH: dx = 0; dy = -1; break;
    case Direction::EAST:  dx = 1; dy = 0;  break;
    case Direction::SOUTH: dx = 0; dy = 1;  break;
    case Direction::WEST:  dx = -1; dy = 0; break;
    }

    for (int hop = hopLength; hop > 0; --hop) {
        int newX = position.x + dx * hop;
        int newY = position.y + dy * hop;

        if (newX >= 0 && newX < boardWidth && newY >= 0 && newY < boardHeight) {
            recordMove(Position(newX, newY));
            return;
        }
    }
}

void Hopper::display() const {
    std::cout << "Hopper ID: " << getId()
              << "\nPosition: (" << getPosition().x << ", " << getPosition().y << ")"
              << "\nDirection: " << directionToString(getDirection())
              << "\nSize: " << getSize()
              << "\nHop Length: " << getHopLength()
              << "\nStatus: " << (isAlive() ? "Alive" : "Dead")
              << "\n" << std::endl;
}

void Hopper::printStatus() const {
    std::cout << "Hopper ID: " << getId()
              << ", Position: (" << getPosition().x << ", " << getPosition().y << ")"
              << ", Direction: " << Bug::directionToString(getDirection())
              << ", Size: " << getSize()
              << ", Hop Length: " << getHopLength()
              << ", Status: " << (isAlive() ? "Alive" : "Dead")
              << std::endl;
}