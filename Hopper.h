#ifndef HOPPER_H
#define HOPPER_H

#include "Bug.h"
#include <cstdlib>

class Hopper : public Bug {
private:
    int hopLength;

public:
    // constructor
    Hopper(int id, Position pos, Direction dir, int size)
        : Bug(id, pos, dir, size) {
        hopLength = 2 + rand() % 3;
    }

    void move() override;
    void display() const override;

    int getHopLength() const { return hopLength; }
    void printStatus() const override;
};

#endif //HOPPER_H