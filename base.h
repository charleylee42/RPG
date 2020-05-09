#ifndef BASE_H
#define BASE_H

#include "main.h"

class Base {
protected:
    int type;
    char shape;
    bool climbable;
    int speed;
    
public:
    Base();
    Base(int type);
    Base(char shape);
    void print();
    
    int getSpeed();
    
    bool isClimbable();
    bool isLava();
    bool isWater();
};

#endif
