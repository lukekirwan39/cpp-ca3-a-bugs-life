//
// Created by araya on 20/04/2025.
//

#include "Jumper.h"
#include <iostream>

Jumper::Jumper(int id, Position pos, Direction dir, int size)
    : Bug(id, pos, dir, size) {
    jumpLength= 2+rand()%4;
}

void Jumper::move() {
    if (!isAlive())return;

    int dx=0;
    int dy=0;

    switch (getDirection()) {
    case Direction::NORTH: dy = -jumpLength; break;
    case Direction::EAST:  dx = jumpLength; break;
    case Direction::SOUTH: dy = jumpLength; break;
    case Direction::WEST:  dx = -jumpLength; break;
    }

    int newX=position.x+dx;
    int newY=position.y+dy;

    while (newX < 0 || newX >= 10 || newY < 0 || newY >= 10) {
        int dirInt = rand() % 4 + 1;
        direction = static_cast<Direction>(dirInt);

        switch (direction) {
        case Direction::NORTH: dy = -jumpLength; dx = 0; break;
        case Direction::EAST:  dx = jumpLength; dy = 0; break;
        case Direction::SOUTH: dy = jumpLength; dx = 0; break;
        case Direction::WEST:  dx = -jumpLength; dy = 0; break;
        }

        newX = position.x + dx;
        newY = position.y + dy;
    }

    Position newPos(newX, newY);
    recordMove(newPos);

}

void Jumper::display() const {
    std::cout<< "Jumper ID: "<<getId()
              <<"\nPosition: (" << getPosition().x << ", " << getPosition().y << ")"
              << "\nDirection: " << directionToString(getDirection())
              << "\nSize: " << getSize()
              << "\nStatus: " << (isAlive() ? "Alive" : "Dead")
              << "\nJump Length: " << jumpLength
              << "\n" << std::endl;

}
void Jumper::printStatus() const  {
    std::cout << "Jumper ID: " << getId()
              << ", Position: (" << getPosition().x << ", " << getPosition().y << ")"
              << ", Direction: " << Bug::directionToString(getDirection())
              << ", Size: " << getSize()
              << ", Jump Length: " << jumpLength
              << ", Status: " << (isAlive() ? "Alive" : "Dead")
              << std::endl;
}