#include <iostream>
#include <iomanip>

using namespace std;

#include "item.h"
#include "unit.h"
#include "hero.h"

#define HERO_RANDOM_HP

//==============================================================================
// class Item
//==============================================================================

Item::Item() { // default constructor
    shape = DEFAULT_ITEM_SHAPE;
    destroy = false;
    moved = false;
}

Item::Item(Item &other) { // copy constructor
    shape = other.shape;
    destroy = other.shape;
    moved = other.shape;
}

Item::Item(char shape, string name, int price) { // general constructor
    this->shape = shape;
    this->name = name;
    this->price = price;
    destroy = false;
    moved = false;
}

Item::~Item() {
}

void Item::print() {
    cout << shape;
}

void Item::printFullSpec() {
    cout << "(" << shape << ") " << setw(20) << left << name << right << " price(" << setw(6) << price << " g) ";
}

int Item::getPrice() {
    return price;
}

bool Item::getDestroy() {
    return destroy;
}

bool Item::getMoved() {
    return moved;
}

#define NUM_ITEM_TYPES 4
Item *createRandomItem() {
    int randomType = rand() % NUM_ITEM_TYPES;
    
    if (randomType == 0) {
        return new Potion();
    }
    else if (randomType == 1) {
        return new Bread();
    }
    else if (randomType == 2) {
        return createRandomArmor();
    }
    else { // if (randomType == 3) {
        return createRandomWeapon();
    }
    
    return NULL;
}

//Item *createItemByID(string itemID) {
//    if (itemID == ITEM_ID_KEY) {
//        return new Key();
//    }
//    else if (itemID == ITEM_ID_POTION) {
//        return new Potion();
//    }
//    else if (itemID == ITEM_ID_BOMB) {
//        Bomb *bomb = new Bomb();
//        return bomb;
//    }
//    else if (itemID == ITEM_ID_ARMOR) {
//        return new Armor();
//    }
//    else if (itemID == ITEM_ID_WEAPON) {
//        return new Weapon();
//    }
//    else {
//        cout << "fatal error: Item::createItemByID(): no such itemID = \"" << itemID << "\"" << endl;
//        exit(1);
//    }
//    
//    return NULL;
//}

// factory function which is used by Board::loadCurrentTile()
Item *createItemByShape(char **map, int rowSize, int colSize, int row, int col) {
    // no multi shape!!
    
    if (map[row][col] == DEFAULT_POTION_SHAPE) {
        return new Potion();
    }
    else if (map[row][col] == DEFAULT_BREAD_SHAPE) {
        return new Bread();
    }
    else if (isArmor(map[row][col])) {
        return createRandomArmorByShape(map[row][col]);
    }
    else if (isWeapon(map[row][col])) {
        return createRandomWeaponByShape(map[row][col]);
    }
    // no else part needed
    
    return NULL;
}

//==============================================================================
// class Potion
//==============================================================================

#define DEFAULT_POTION_RANGE 201
Potion::Potion() : Item(DEFAULT_POTION_SHAPE, DEFAULT_POTION_NAME, DEFAULT_POTION_PRICE) { // default constructor
    // first sol:
    //hp = (rand() % DEFAULT_POTION_RANGE) - 100; // range: -100 ~ 100
    
    poison = rand() % 2; // 0 false / 1 true
    
    hp = DEFAULT_POTION_HP;
    mp = DEFAULT_POTION_MP;
}

Potion::Potion(Potion &other) : Item(other) { // copy constructor
    hp = other.hp;
    mp = other.mp;
}

Potion::Potion(char shape, string name, int price, int hp, int mp) : Item(shape, name, price) { // general constructor
    this->hp = hp;
    this->mp = mp;
}

Potion::~Potion() {
}

void Potion::printFullSpec() {
    Item::printFullSpec();
    cout << " hp(" << hp << ") mp(" << mp << ")";
}

bool Potion::use(Unit *unit) {
    if (poison) {
        unit->decHp(hp);
    }
    else {
        unit->incHp(hp);
    }
    destroy = true;
    return true;
}

Item *Potion::clone() {
    return new Potion(*this);
}

//==============================================================================
// class Bread
//==============================================================================

#define DEFAULT_BREAD_RANGE 11
Bread::Bread() : Item(DEFAULT_BREAD_SHAPE, DEFAULT_BREAD_NAME, DEFAULT_BREAD_PRICE) { // default constructor
    speed = rand() % 11 - 5;
}

Bread::Bread(Bread &other) : Item(other) { // copy constructor
    speed = other.speed;
}

Bread::Bread(char shape, string name, int price, int speed) : Item(shape, name, price) { // general constructor
    this->speed = speed;
}

Bread::~Bread() {
}

void Bread::printFullSpec() {
    Item::printFullSpec();
    cout << " speed(" << speed << ")";
}

bool Bread::use(Unit *unit) {
    unit->incSpeed(speed);
    destroy = true;
    return true;
}

Item *Bread::clone() {
    return new Bread(*this);
}

//==============================================================================
// class Weapon
//==============================================================================

Weapon::Weapon() : Item(WEAPON_SHAPE_ONE_HAND, DEFAULT_WEAPON_NAME, DEFAULT_WEAPON_PRICE) {
    atk = DEFAULT_WEAPON_ATK;
    numHands = WEAPON_ONE_HAND;
}

Weapon::Weapon(Weapon &other) : Item(other) { // copy constructor
    atk = other.atk;
    numHands = other.numHands;
}

Weapon::Weapon(char shape, string name, int price, int atk, int numHands) : Item(shape, name, price) {
    this->atk = atk;
    this->numHands = atk;
}

Weapon::~Weapon() {
}

void Weapon::printFullSpec() {
    Item::printFullSpec();
    cout << " atk(" << atk << ") numHands(" << numHands << ")";
}

int Weapon::getAtk() {
    return atk;
}

bool Weapon::use(Unit *unit) {
    if (unit == NULL) {
        return false;
    }
    
    // equipí•˜ëŠ” ì½”ë“œê°€ ë“¤ì–´ì™€ì•¼ í•¨.
    if (((Hero *)unit)->equip(this)) {
        moved = true;
    }
    
    return false;
}

Item *Weapon::clone() {
    return new Weapon(*this);
}

Weapon *createRandomWeapon() {
    return createRandomWeapon(ITEM_SHAPE_NONE);
}

/*
 // class Paperdoll/Item related
 #define BODY_PART_ID_LEFT_HAND 7
 #define BODY_PART_ID_RIGHT_HAND 8
 
 #define WEAPON_ONE_HAND 1 
 #define WEAPON_TWO_HAND 2
 
 #define WEAPON_SHAPE_ONE_HAND '!'
 #define WEAPON_SHAPE_TWO_HAND '?'
 */
#define NUM_RANDOM_WEAPONS 3
Weapon *createRandomWeapon(char shapeToCreate) {
    char shape[NUM_RANDOM_WEAPONS] =             {WEAPON_SHAPE_ONE_HAND,     WEAPON_SHAPE_ONE_HAND,      WEAPON_SHAPE_TWO_HAND};
    char name[NUM_RANDOM_WEAPONS][80] =          {"Wizard\'s Wand",          "Poseidon\'s Sword",        "Zeus\' Staff"};
    int price[NUM_RANDOM_WEAPONS] =              {100,                       1000,                       100000};
  //int duarability[NUM_RANDOM_WEAPONS] =        {100,                       1000,                       100000};
    int atk[NUM_RANDOM_WEAPONS] =                {1,                         100,                        1000};
    int numHands[NUM_RANDOM_WEAPONS] =           {WEAPON_ONE_HAND,           WEAPON_ONE_HAND,            WEAPON_TWO_HAND};
    
    int randIndex = -1;
    if (shapeToCreate == ITEM_SHAPE_NONE) {
        randIndex = rand() % NUM_RANDOM_WEAPONS;
    }
    else {
        while (true) {
            randIndex = rand() % NUM_RANDOM_WEAPONS;
            
            if (shape[randIndex] == shapeToCreate) {
                break;
            }
        }
    }
    
    return new Weapon(shape[randIndex],
                      name[randIndex],
                      price[randIndex],
                      //duarability[randIndex],
                      atk[randIndex],
                      numHands[randIndex]);
}

Weapon *createRandomWeaponByShape(char shape) {
    return createRandomWeapon(shape);
}

bool isWeapon(char shape) {
    return 
    WEAPON_SHAPE_ONE_HAND == shape ||
    WEAPON_SHAPE_TWO_HAND == shape;
}

//==============================================================================
// class Armor
//==============================================================================

Armor::Armor() : Item(ARMOR_SHAPE_HEAD, DEFAULT_ARMOR_NAME, DEFAULT_ARMOR_PRICE) {
    def = DEFAULT_ARMOR_DEF;
    bodyPartID = BODY_PART_ID_HEAD;
}

Armor::Armor(Armor &other) : Item(other) { // copy constructor
    def = other.def;
    bodyPartID = other.bodyPartID;
}

Armor::Armor(char shape, string name, int price, int def, int bodyPartID) : Item(shape, name, price) {
    this->def = def;
    this->bodyPartID = bodyPartID;
}

Armor::~Armor() {
}

void Armor::printFullSpec() {
    Item::printFullSpec();
    cout << " def(" << def << ") bodyPartID(" << bodyPartID << ")";
}

int Armor::getDef() {
    return def;
}

int Armor::getBodyPartID() {
    return bodyPartID;
}

bool Armor::isArmor() {
    return true;
}

bool Armor::use(Unit *unit) {
    if (unit == NULL) {
        return false;
    }
    
    // equipí•˜ëŠ” ì½”ë“œê°€ ë“¤ì–´ì™€ì•¼ í•¨.
    if (((Hero *)unit)->equip(this)) {
        moved = true;
    }
    
    return false;
}

Item *Armor::clone() {
    return new Armor(*this);
}

Armor *createRandomArmor() {
    return createRandomArmor(ITEM_SHAPE_NONE);
}

/*
#define DEFAULT_ARMOR_SHAPE_HEAD 'A'
#define DEFAULT_ARMOR_SHAPE_CHEST 'W'
#define DEFAULT_ARMOR_SHAPE_BACK 'Q'
#define DEFAULT_ARMOR_SHAPE_HANDS 'U'
#define DEFAULT_ARMOR_SHAPE_LEGS 'L'
#define DEFAULT_ARMOR_SHAPE_FEET 'F'

#define BODY_PART_ID_HEAD 0
#define BODY_PART_ID_CHEST 1
#define BODY_PART_ID_BACK 2
#define BODY_PART_ID_HANDS 3
#define BODY_PART_ID_LEGS 4
#define BODY_PART_ID_FEET 5
*/

#define NUM_RANDOM_ARMORS 3
Armor *createRandomArmor(char shapeToCreate) {
    char shape[NUM_RANDOM_ARMORS] =             {ARMOR_SHAPE_HEAD,  ARMOR_SHAPE_FEET,       ARMOR_SHAPE_CHEST};
    char name[NUM_RANDOM_ARMORS][80] =          {"Wizard\'s Hat",   "Poseidon\'s Boots",    "Zeus\' Chest"};
    int price[NUM_RANDOM_ARMORS] =              {100,               1000,                   100000};
  //int duarability[NUM_RANDOM_ARMORS] =        {100,               1000,                   100000};
    int def[NUM_RANDOM_ARMORS] =                {1,                 100,                    1000};
    int bodyPartID[NUM_RANDOM_ARMORS] =         {BODY_PART_ID_HEAD, BODY_PART_ID_FEET,      BODY_PART_ID_CHEST};
    
    int randIndex = -1;
    if (shapeToCreate == ITEM_SHAPE_NONE) {
        randIndex = rand() % NUM_RANDOM_ARMORS;
    }
    else {
        while (true) {
            randIndex = rand() % NUM_RANDOM_ARMORS;
            
            if (shape[randIndex] == shapeToCreate) {
                break;
            }
        }
    }
    
    return new Armor(shape[randIndex],
                     name[randIndex],
                     price[randIndex],
                     //duarability[randIndex],
                     def[randIndex],
                     bodyPartID[randIndex]);
}

Armor *createRandomArmorByShape(char shape) {
    return createRandomArmor(shape);
}

bool isArmor(char shape) {
    return 
    ARMOR_SHAPE_HEAD == shape ||
    ARMOR_SHAPE_CHEST == shape ||
    ARMOR_SHAPE_BACK == shape ||
    ARMOR_SHAPE_HANDS == shape ||
    ARMOR_SHAPE_LEGS == shape ||
    ARMOR_SHAPE_FEET == shape;}

//==============================================================================
// class Key
//==============================================================================

Key::Key() : Item(DEFAULT_KEY_SHAPE, 0, 0) { // default constructor
}

Key::Key(Key &other) : Item(other) { // copy constructor
}

Key::Key(char shape, string name, int price) : Item(shape, name, price) { // general constructor
}

Key::~Key() {
}

bool Key::use(Unit *unit) {
    
    destroy = true;
    return true;
}

Item *Key::clone() {
    return new Key(*this);
}
