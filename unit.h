#ifndef UNIT_H
#define UNIT_H

#include "main.h"

class Item;
class Prop;
class Board;
class Hero;

class Unit { // abstract class
protected:
    char shapeOriginal;
    char shape;
    int row;
    int col;
    
    int maxHp;
    int hp;
    
    int maxMp;
    int mp;
    
    int exp;
    int gold;

    int atk;
    //int def;
        
    int speed;

    bool died;

    bool frozen;
    int frozenDelay;
    
    bool stunned;
    int stunnedDelay;
    
    bool isAlly;
    int isAllyDelay;
    
    Unit *unitEngaged;
    
    Board *board;
    
public:
    Unit();
    Unit(char shape);
    Unit(char shape, int row, int col, int maxHp, int hp, int maxMp, int mp, int atk, int exp, int gold, int sp);
    void print();
    virtual void printStat();
    char getShape();
    
    int getRow();
    void setRow(int row);
    int getCol();
    void setCol(int col);
    
    int getMaxHp();
    int getHp();
    void incHp(int hpToInc);
    void decHp(int hpToDec);

    int getMaxMp();
    int getMp();
    void incMp(int mpToInc);
    void decMp(int mpToDec);

    int getAtk();

    int getExp();
    void incExp(int expToInc);

    int getGold();
    void incGold(int goldToInc);
    void decGold(int goldToDec);
    
    int getSpeed();
    void incSpeed(int speedToInc);
    void decSpeed(int speedToDec);
    
    bool isDead();
    
    void freeze(int debufDelay);
    void unfreeze();
    
    void stun(int debufDelay);
    void destun();
    
    void ally(int debufDelay);
    void deally();
    
    void setBoard(Board *board);
    
    virtual void move(int dir) = 0; // pure virtual function
    virtual bool useItem(int index) = 0; // pure virtual function
    
    virtual bool isHero();
    virtual bool isMonster();
    virtual bool isMerchant();

    virtual bool isRidable();
    
    virtual bool isSkyUnit();
    virtual bool isWaterUnit();
    
    virtual bool isAirBalloon();
    virtual bool isBoat();
    virtual bool getOff(Unit *unit); // ridableë§Œ ë§Œë“ ë‹¤.
        
    virtual Hero *getHero();
    virtual void setHero(Hero *hero);
        
    void morph(char shape);
    void unmorph();
    
    virtual Unit *getUnitEngaged();
    virtual void setUnitEngaged(Unit *unit);
    
    virtual bool hasRoom();
    virtual void receiveItem(Item *item);
    
    virtual void interact(Unit *unit); // virtual function
    virtual void effect(Unit *unit, Item *item, Prop *prop, int skillNumber);
};

#endif
