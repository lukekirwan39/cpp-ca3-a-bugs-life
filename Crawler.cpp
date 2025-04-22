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

    for (int i = 0; i < 4; ++i) {
        int randDir = rand() % 4;
        Position newPos = position;

        switch (randDir) {
            case 0: newPos.y--; break;
            case 1: newPos.x++; break;
            case 2: newPos.y++; break;
            case 3: newPos.x--; break;
        }

        if (newPos.x >= 0 && newPos.x < 10 && newPos.y >= 0 && newPos.y < 10) {
            direction = static_cast<Direction>(randDir);
            position = newPos;
            path.push_back(newPos);
            return;
        }
    }
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