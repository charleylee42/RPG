#ifndef MONSTER_H
#define MONSTER_H

#include "main.h"

// the child class of class Unit
class Monster : public Unit {
protected:
public:
    Monster();    
    Monster(char shape, int row, int col, int maxHp, int hp, int maxMp, int mp, int atk, int exp, int gold);
    
    virtual void move(int dir);
    virtual bool useItem(int index);
    
    virtual bool isMonster();

    virtual void interact(Unit *unit); // virtual function
};

#endif
