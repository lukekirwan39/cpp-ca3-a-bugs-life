//
// Created by araya on 20/04/2025.
//

#ifndef JUMPER_H
#define JUMPER_H
#include <iostream>
#include <cstdlib>

#include "Bug.h"




class Jumper : public Bug{
    private:
    int jumpLength;

    public:
    Jumper(int id, Position pos, Direction dir, int size);

    void move() override ;
    void display() const override;

    void printStatus() const override;



};



#endif //JUMPER_H
