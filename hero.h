#ifndef HERO_H
#define HERO_H

#include "main.h"
#include "item.h"
#include "inventory.h"
#include "unit.h"

// the child class of class Unit
class Hero : public Unit {
protected:
    Inventory *slots;
    Weapon *rightHand;

    Unit *ride;
    
public:
    Hero();    
    Hero(char shape, int row, int col, int maxHp, int hp, int maxMp, int mp, int atk, int exp, int gold, int slotsCapacity, int speed);
    
    virtual void printStat();
    
    virtual void move(int dir);
    virtual bool useItem(int index);
    
//    virtual bool unlockChest(int index);
    
    virtual bool isHero();

    void effect(Unit *unit, Item *item, Prop *prop, int skillNumber);
    void affectByTile();
    
    void getOff();
    bool equip(Item *item);
    
    virtual bool hasRoom();
    virtual void receiveItem(Item *item);
};

// the child class of class Unit
class AirBalloon : public Unit {
protected:
    Hero *hero;

public:
    AirBalloon();
    AirBalloon(char shape, int row, int col, int speed);
    
    virtual void printStat();
    
    virtual Hero *getHero();
    virtual void setHero(Hero *hero);
    
    virtual void move(int dir);
    virtual bool useItem(int index);
    
    virtual bool isRidable();
    virtual bool isSkyUnit();
    virtual bool isAirBalloon();
    virtual bool getOff(Unit *unit); // ridableë§Œ ë§Œë“ ë‹¤.

    //void effect(Unit *unit, Item *item, Prop *prop, int skillNumber);
    //void affectByTile();
};
class Boat : public Unit {
protected:
    Hero *hero;
    
public:
    Boat();
    Boat(char shape, int row, int col, int speed);
    
    virtual void printStat();
    
    virtual Hero *getHero();
    virtual void setHero(Hero *hero);
    
    virtual void move(int dir);
    virtual bool useItem(int index);
    
    virtual bool isBoat();
    virtual bool isRidable();
    virtual bool isWaterUnit();
    virtual bool getOff(Unit *unit); // ridableë§Œ ë§Œë“ ë‹¤.

    //void effect(Unit *unit, Item *item, Prop *prop, int skillNumber);
    //void affectByTile();
};

#endif
