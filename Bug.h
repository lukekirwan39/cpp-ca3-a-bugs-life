#ifndef BUG_H
#define BUG_H
#include <string>

#include <vector>
#include <SFML/Graphics.hpp>

enum class Direction { NORTH = 1, EAST, SOUTH, WEST };

struct Position {
    int x;
    int y;
    Position(int x = 0, int y = 0) : x(x), y(y) {}
};

class Bug {
protected:
    int id;
    Position position;
    Direction direction;
    int size;
    bool alive;
    std::vector<Position> path;

public:
    // constructor
    Bug(int id, Position pos, Direction dir, int size)
        : id(id), position(pos), direction(dir), size(size), alive(true) {
        path.push_back(pos);
    }

    // destructor
    virtual ~Bug() {}

    virtual void move() = 0;
    virtual void display() const = 0;
    virtual void printStatus() const = 0;

    bool isWayBlocked(int boardWidth, int boardHeight) {
        switch (direction) {
        case Direction::NORTH: return position.y == 0;
        case Direction::EAST:  return position.x == boardWidth - 1;
        case Direction::SOUTH: return position.y == boardHeight - 1;
        case Direction::WEST:  return position.x == 0;
        }
        return false;
    }

    // getters
    int getId() const { return id; }
    Position getPosition() const { return position; }
    Direction getDirection() const { return direction; }
    int getSize() const { return size; }
    bool isAlive() const { return alive; }
    const std::vector<Position>& getPath() const { return path; }

    // setters
    void setAlive(bool status) { alive = status; }

    void recordMove(Position newPos) {
        position = newPos;
        path.push_back(newPos);
    }

    static std::string directionToString(Direction dir);
};

#endif // BUG_H