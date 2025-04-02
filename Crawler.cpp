
#include "Crawler.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

Crawler::Crawler(int id, Position startPos, Direction direction, int size)
    : id(id), position(startPos), direction(direction), size(size), alive(true){
    path.push_back(position);
    std::srand(std::time(nullptr));
}

void Crawler::move(int boardWidth, int boardHeight){
    if (!alive) return;

    while (isWayBlocked(boardWidth, boardHeight)){
        direction = static_cast<Direction>((std::rand() % 4) + 1);
    }

    switch (direction){
        case Direction::NORTH: position.y -= 1; break;
        case Direction::EAST: position.x += 1; break;
        case Direction::SOUTH: position.y += 1; break;
        case Direction::WEST: position.x -= 1; break;
    }

    path.push_back(position);
}

bool Crawler::isWayBlocked(int boardWidth, int boardHeight) const{
    switch (direction){
        case Direction::NORTH: return position.y == 0;
        case Direction::EAST: return position.x >= boardWidth - 1;
        case Direction::SOUTH: return  position.y >= boardHeight - 1;
        case Direction::WEST: return position.x == 0;
    }

    return true;
}

// getter methods
int Crawler::getId() const{ return id; }
Position Crawler::getPosition() const{ return position; }
Direction Crawler::getDirection() const{ return direction; }
int Crawler::getSize() const{ return size; }
bool Crawler::isAlive() const{ return alive; }
std::list<Position> Crawler::getPath() const{ return path; }

// setter methods
void Crawler::setDirection(Direction newDir){ direction = newDir; }
void Crawler::setAlive(bool status){ alive = status; }



void Crawler::printStatus() const{
    std::cout << "Crawler ID: " << id
    << " | Pos: (" << position.x << "," << position.y << ")"
    << " | Size: " << size << " | Alive: " << (alive ? "Yes" : "No")
    << " | Direction: ";
    switch (direction){
        case Direction::NORTH: std::cout << "North"; break;
        case Direction::EAST: std::cout << "East"; break;
        case Direction::SOUTH: std::cout << "South"; break;
        case Direction::WEST: std::cout << "West"; break;
    }

    std::cout << std::endl;
}

void Crawler::displayCrawler() const {
        std::cout << "ID: " << id
                  << ", Position: (" << position.x << ", " << position.y << ")"
                  << ", Direction: " << getDirectionAsString()
                  << ", Size: " << size << "\n";
}




