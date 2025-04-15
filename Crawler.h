#ifndef CRAWLER_H
#define CRAWLER_H

#include "Bug.h"

class Crawler : public Bug{
private:
    int killerId = -1;

public:
    // constructor
    Crawler(int id, Position startPos, Direction dir, int size);

    // getters
    int getKillerId() const;

    // setters
    void setKillerId(int x);

    // movement logic
    void move() override;

    void printStatus() const override;
    void display() const override;
    void grow(int amount);
};



#endif //CRAWLER_H
