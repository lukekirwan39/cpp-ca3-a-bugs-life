#ifndef BUG_H
#define BUG_H

#include <string>
#include <vector>

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
    int killerId;
    std::vector<Position> path;

public:
    Bug(int id, Position pos, Direction dir, int size)
        : id(id), position(pos), direction(dir), size(size), alive(true), killerId(-1) {
        path.push_back(pos);
    }

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

    int getId() const { return id; }
    Position getPosition() const { return position; }
    Direction getDirection() const { return direction; }
    int getSize() const { return size; }
    bool isAlive() const { return alive; }
    const std::vector<Position>& getPath() const { return path; }
    int getKillerId() const { return killerId; }

    void setAlive(bool status) { alive = status; }
    void setKillerId(int id) { killerId = id; }

    void recordMove(Position newPos) {
        position = newPos;
        path.push_back(newPos);
    }

    void grow(int amount) { size += amount; }

    static std::string directionToString(Direction dir);
};

#endif // BUG_H