#include "Crawler.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

Crawler::Crawler(int id, Position startPos, Direction dir, int size)
    : Bug(id, startPos, dir, size) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
}

void Crawler::move() {
    if (!isAlive()) return;

    while (isWayBlocked(10, 10)) {
        direction = static_cast<Direction>((std::rand() % 4) + 1);
    }

    Position newPos = getPosition();

    switch (getDirection()) {
        case Direction::NORTH: newPos.y--; break;
        case Direction::EAST:  newPos.x++; break;
        case Direction::SOUTH: newPos.y++; break;
        case Direction::WEST:  newPos.x--; break;
    }

    recordMove(newPos);
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
