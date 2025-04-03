
#ifndef CRAWLER_H
#define CRAWLER_H

#include <list>
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>

struct Position{
    int x;
    int y;
};

enum class Direction{
    NORTH = 1,
    EAST,
    SOUTH,
    WEST
};

class Crawler {
private:
    int id;
    Position position;
    Direction direction;
    int size;
    bool alive;
    std::list<Position> path;
    int killerId = -1;

public:
    // constructor
    Crawler(int id, Position startPos, Direction dir, int size);

    // getters
    int getId() const;
    Position getPosition() const;
    Direction getDirection() const;
    int getSize() const;
    bool isAlive() const;
    int getKillerId() const;
    std::list<Position> getPath() const;

    // setters
    void setDirection(Direction newDir);
    void setAlive(bool status);
    void setKillerId(int x);

    // movement logic
    void move(int boardWidth, int boardHeight);
    bool isWayBlocked(int boardWidth, int boardHeight) const;

    void printStatus() const;
    void displayCrawler() const;
    void grow(int amount);
    std::string getDirectionAsString() const;
};



#endif //CRAWLER_H
