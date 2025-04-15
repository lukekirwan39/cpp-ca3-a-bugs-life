#include "Hopper.h"
#include <iostream>
#include <cstdlib>

void Hopper::move() {
    int dx = 0, dy = 0;

    switch (direction) {
    case Direction::NORTH: dy = -1; break;
    case Direction::EAST:  dx = 1;  break;
    case Direction::SOUTH: dy = 1;  break;
    case Direction::WEST:  dx = -1; break;
    }

    const int boardWidth = 10;
    const int boardHeight = 10;

    int newX = position.x + dx * hopLength;
    int newY = position.y + dy * hopLength;

    while (newX < 0 || newX >= boardWidth || newY < 0 || newY >= boardHeight) {
        int dirInt = 1 + rand() % 4;
        direction = static_cast<Direction>(dirInt);

        switch (direction) {
        case Direction::NORTH: dx = 0; dy = -1; break;
        case Direction::EAST:  dx = 1; dy = 0; break;
        case Direction::SOUTH: dx = 0; dy = 1; break;
        case Direction::WEST:  dx = -1; dy = 0; break;
        }

        newX = position.x + dx * hopLength;
        newY = position.y + dy * hopLength;
    }

    int actualHop = hopLength;
    while (newX < 0 || newX >= boardWidth || newY < 0 || newY >= boardHeight) {
        actualHop--;
        newX = position.x + dx * actualHop;
        newY = position.y + dy * actualHop;
    }

    Position newPos(newX, newY);
    recordMove(newPos);
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