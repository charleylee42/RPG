#ifndef MERCHANT_H
#define MERCHANT_H

#include "main.h"

class Inventory;

// the child class of class Unit
class Merchant : public Unit {
protected:
    Inventory *itemsToSell;
    Inventory *itemsBought;

public:
    Merchant();    
    Merchant(char shape, int row, int col, int maxHp, int hp, int maxMp, int mp, int atk, int exp, int gold);
    
    virtual void move(int dir);
    virtual bool useItem(int index);
    
    virtual bool isMerchant();
    
    virtual void interact(Unit *unit); // virtual function
};

#endif
