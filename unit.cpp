#include <iostream>

using namespace std;

#include "board.h"
#include "item.h"
#include "prop.h"
#include "unit.h"

//==============================================================================
// class Unit
//==============================================================================
#define SPEED_MAX 5
#define SPEED_NORMAL 0
#define SPEED_MIN -5

Unit::Unit() { // default constructor
    shapeOriginal = DEFAULT_UNIT_SHAPE;
    shape = DEFAULT_UNIT_SHAPE;
    row = -1;
    col = -1;
    
    maxHp = DEFAULT_UNIT_MAX_HP;
    hp = DEFAULT_UNIT_HP;
    maxMp = DEFAULT_UNIT_MAX_MP;
    mp = DEFAULT_UNIT_MP;
    atk = DEFAULT_UNIT_ATK;
    exp = DEFAULT_UNIT_EXP;
    gold = DEFAULT_UNIT_GOLD;
    speed = DEFAULT_UNIT_SPEED;

    died = false;
    
    frozen = false;
    frozenDelay = DEBUF_FOREVER;
    
    stunned = false;
    stunnedDelay = DEBUF_FOREVER;
    
    isAlly = false;
    isAllyDelay = DEBUF_FOREVER;
    
    unitEngaged = NULL;
    
    board = NULL;
}

Unit::Unit(char shape) { // general constructor
    shapeOriginal = shape;
    this->shape = shape;
    row = -1;
    col = -1;

    maxHp = DEFAULT_UNIT_MAX_HP;
    hp = DEFAULT_UNIT_HP;
    maxMp = DEFAULT_UNIT_MAX_MP;
    mp = DEFAULT_UNIT_MP;
    atk = DEFAULT_UNIT_ATK;
    exp = DEFAULT_UNIT_EXP;
    gold = DEFAULT_UNIT_GOLD;
    speed = DEFAULT_UNIT_SPEED;

    died = false;
    frozen = false;
    

    unitEngaged = NULL;

    board = NULL;
}

Unit::Unit(char shape, int row, int col, int maxHp, int hp, int maxMp, int mp, int atk, int exp, int gold, int sp) { // general constructor
    shapeOriginal = shape;
    this->shape = shape;
    this->row = row;
    this->col = col;
    this->maxHp = maxHp;
    this->hp = hp;
    this->maxMp = maxMp;
    this->mp = mp;
    this->atk = atk;
    this->exp = exp;
    this->gold = gold;
    this->speed = speed;

    died = false;
    frozen = false;
    
    unitEngaged = NULL;

    board = NULL;
}

void Unit::print() {
    cout << shape;
}

void Unit::printStat() {
    cout << shape << ": hp(" << hp << ") mp(" << mp
         << ") atk(" << atk << ") exp(" << exp
         << ") gold(" << gold << ") speed(" << speed << ")";
}

char Unit::getShape() {
    return shape;
}

int Unit::getRow() {
    return row;
}

void Unit::setRow(int row) {
    this->row = row;
}

int Unit::getCol() {
    return col;
}

void Unit::setCol(int col) {
    this->col = col;
}

int Unit::getMaxHp() {
    return maxHp;
}

int Unit::getHp() {
    return hp;
}

void Unit::incHp(int hpToInc) {
    if (hp + hpToInc >= maxHp) {
        hp = maxHp;
    }
    else {
        hp += hpToInc;
    }
}

void Unit::decHp(int hpToDec) {
    if (hp - hpToDec <= 0) {
        hp = 0;
        died = true;
    }
    else {
        hp -= hpToDec;
    }
}

int Unit::getMaxMp() {
    return maxMp;
}

int Unit::getMp() {
    return mp;
}

void Unit::incMp(int mpToInc) {
    if (mp + mpToInc >= maxMp) {
        mp = maxMp;
    }
    else {
        mp += mpToInc;
    }
}

void Unit::decMp(int mpToDec) {
    if (mp - mpToDec <= 0) {
        mp = 0;
    }
    else {
        mp -= mpToDec;
    }
}

int Unit::getExp() {
    return exp;
}

int Unit::getAtk() {
    return atk;
}

void Unit::incExp(int expToInc) {
    exp += expToInc;
}

int Unit::getGold(){
    return gold;
}

void Unit::incGold(int goldToInc) {
    gold += goldToInc;
}

// pre-condition: gold - goldTodec >= 0
void Unit::decGold(int goldToDec) {
    gold -= goldToDec;
}

int Unit::getSpeed() {
    return speed;
}

void Unit::incSpeed(int speedToInc) {
    if (speed + speedToInc >= SPEED_MAX) {
        speed = SPEED_MAX;
    }
    else if (speed + speedToInc <= SPEED_MIN) {
        speed = SPEED_MIN;
    }
    else {
        speed += speedToInc;
    }
}

void Unit::decSpeed(int speedToDec) {
    if (speed - speedToDec <= 0) {
        speed = 0;
        died = true;
    }
    else {
        speed -= speedToDec;
    }
}

bool Unit::isDead() {
    return died;
}


void Unit::freeze(int debufDelay) {
    frozen = true;
    frozenDelay = debufDelay;
}

void Unit::unfreeze() {
    frozen = false;
    frozenDelay = 0;
}

void Unit::stun(int debufDelay) {
    stunned = true;
    stunnedDelay = debufDelay;
}    

void Unit::destun() {
    stunned = false;
    stunnedDelay = 0;
}   
void Unit::ally(int debufDelay) {
    isAlly = true;
    isAllyDelay = debufDelay;
}
void Unit::deally() {
    isAlly = false;
    isAllyDelay = 0;
}

void Unit::setBoard(Board *board) {
    this->board = board;
}

bool Unit::isHero() {
    // N/A
    return false;
}

bool Unit::isMonster() {
    // N/A
    return false;
}

bool Unit::isMerchant() {
    // N/A
    return false;
}

bool Unit::isRidable() {
    // N/A
    return false;
}

bool Unit::isSkyUnit() {
    // N/A
    return false;
}

bool Unit::isWaterUnit() {
    // N/A
    return false;
}

bool Unit::isAirBalloon() {
    // N/A
    return false;
}

bool Unit::isBoat() {
    // N/A
    return false;
}

bool Unit::getOff(Unit *unit) {
    // N/A
    return false;
}

Hero *Unit::getHero() {
    // N/A
    return NULL;
}

void Unit::setHero(Hero *hero) {
    // N/A
}

void Unit::morph(char shape) {
    this->shape = shape;
}

void Unit::unmorph() {
    shape = shapeOriginal;
}

Unit *Unit::getUnitEngaged() {
    return unitEngaged;
}

void Unit::setUnitEngaged(Unit *unit) {
    unitEngaged = unit;
}

bool Unit::hasRoom() {
    return false;
}

void Unit::receiveItem(Item *item) {
}

void Unit::interact(Unit *unit) {
    // N/A
}

void Unit::effect(Unit *unit, Item *item, Prop *prop, int skillNumber) {
    // N/A
}
