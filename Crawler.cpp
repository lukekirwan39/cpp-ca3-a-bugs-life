#include "Crawler.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

Crawler::Crawler(int id, Position startPos, Direction dir, int size)
    : Bug(id, startPos, dir, size) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
}

void Crawler::move() {
    if (!alive) return;

    Position newPos = position;

    switch (direction) {
    case Direction::NORTH: newPos.y--; break;
    case Direction::EAST:  newPos.x++; break;
    case Direction::SOUTH: newPos.y++; break;
    case Direction::WEST:  newPos.x--; break;
    }

    // Prevent off-board movement (assuming 0–9 grid)
    if (newPos.x < 0 || newPos.x >= 10 || newPos.y < 0 || newPos.y >= 10) {
        // Change direction randomly if blocked
        direction = static_cast<Direction>(rand() % 4);
        return; // skip move this cycle
    }

    position = newPos;
    path.push_back(newPos);
}

void Crawler::grow(int amount) {
    size += amount;
}

void Crawler::setKillerId(int id) {
    killerId = id;
}

int Crawler::getKillerId() const {
    return killerId;
}

void Crawler::printStatus() const {
    std::cout << "Crawler ID: " << getId()
              << " | Pos: (" << getPosition().x << "," << getPosition().y << ")"
              << " | Size: " << getSize()
              << " | Alive: " << (isAlive() ? "Yes" : "No")
              << " | Direction: " << directionToString(getDirection())
              << std::endl;
}

void Crawler::display() const {
    std::cout << "Crawler ID: " << getId()
              << "\nPosition: (" << getPosition().x << ", " << getPosition().y << ")"
              << "\nDirection: " << directionToString(getDirection())
              << "\nSize: " << getSize()
              << "\nStatus: " << (isAlive() ? "Alive" : "Dead")
              << "\n" << std::endl;
}
