#include "Bug.h"

std::string Bug::directionToString(Direction dir) {
    switch (dir) {
    case Direction::NORTH: return "North";
    case Direction::EAST:  return "East";
    case Direction::SOUTH: return "South";
    case Direction::WEST:  return "West";
    default: return "Unknown";
    }
}