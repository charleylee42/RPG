#ifndef ITEM_H
#define ITEM_H

#include "main.h"
#include "unit.h"
#include "prop.h"

class Item { // abstract class
protected:
    char shape;
    
    string name;
    int price;
    
    bool destroy;
    bool moved;
    
public:
    Item();
    Item(Item &other);
    Item(char shape, string name, int price);

    virtual ~Item();

    void print();
    virtual void printFullSpec();
    
    int getPrice();
    
    bool getDestroy();
    bool getMoved();

    virtual bool use(Unit *unit) = 0; // pure virtual function
    //virtual void effect(Unit *unit, Item *item, Prop *prop);
    
    virtual Item *clone() = 0;
};

Item *createRandomItem();
Item *createItemByID(string itemID);
// factory function which is used by Board::loadCurrentTile()
Item *createItemByShape(char **map, int rowSize, int colSize, int row, int col);

class Potion : public Item {
protected:
    bool poison;
    
    int hp;
    int mp;
    
public:
    Potion();
    Potion(Potion &other);
    Potion(char shape, string name, int price, int hp, int mp);    
    virtual ~Potion();

    virtual void printFullSpec();

    virtual bool use(Unit *unit);
    
    virtual Item *clone();
};

class Bread : public Item {
protected:
    int speed;
    
public:
    Bread();
    Bread(Bread &other);
    Bread(char shape, string name, int price, int speed);    
    virtual ~Bread();
    
    virtual void printFullSpec();
    
    virtual bool use(Unit *unit);
    
    virtual Item *clone();
};

class Key : public Item {
protected:
    
public:
    Key();
    Key(Key &other);
    Key(char shape, string name, int price);    
    virtual ~Key();
        
    virtual bool use(Unit *unit);
    
    virtual Item *clone();
};

class Weapon : public Item {
protected:
    int atk;
    int numHands;

public:
    Weapon();
    Weapon(Weapon &other);
    Weapon(char shape, string name, int price, int atk, int numHands);    
    virtual ~Weapon();
    
    virtual void printFullSpec();

    int getAtk();
    
    virtual bool use(Unit *unit);
    
    virtual Item *clone();
};

Weapon *createRandomWeapon();
Weapon *createRandomWeapon(char shapeToCreate);
//Weapon *createRandomWeaponByNumHands(int numHands);
Weapon *createRandomWeaponByShape(char shape);
bool isWeapon(char shape);

class Armor : public Item {
protected:
    int def;
    int bodyPartID;
    
public:
    Armor();
    Armor(Armor &other);
    Armor(char shape, string name, int price, int def, int bodyPartID);    
    virtual ~Armor();
    
    virtual void printFullSpec();

    int getDef();
    int getBodyPartID();
    
    virtual bool isArmor();
    
    virtual bool use(Unit *unit);
    
    virtual Item *clone();
};

Armor *createRandomArmor();
Armor *createRandomArmor(char shapeToCreate);
//Armor *createRandomArmorByBodyPartID(int bodyPartID);
Armor *createRandomArmorByShape(char shape);
bool isArmor(char shape);

#endif
