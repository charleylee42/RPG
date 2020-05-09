#ifndef FX_H
#define FX_H

#include "main.h"

class Fx {
protected:
    int dmg;
    int spd;
    char shape;
    bool heroUse;
public:
    Fx();
    Fx(int dmg, int spd);
    Fx(char shape);
    void print();
    
    bool doesHeroUse();
};


#endif
