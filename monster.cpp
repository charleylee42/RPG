#include <iostream>

using namespace std;

#include "main.h"
#include "board.h"
#include "monster.h"

Monster::Monster() : Unit(DEFAULT_MONSTER_SHAPE, -1, -1, DEFAULT_MONSTER_MAX_HP, DEFAULT_MONSTER_HP,
                          DEFAULT_MONSTER_MAX_MP, DEFAULT_MONSTER_MP, DEFAULT_MONSTER_ATK,
                          DEFAULT_MONSTER_EXP, DEFAULT_MONSTER_GOLD, DEFAULT_ALLY_SHAPE) {
}

Monster::Monster(char shape, int row, int col, int maxHp, int hp, int maxMp, int mp, int atk, int exp, int gold)
    : Unit(shape, row, col, maxHp, hp, maxMp, mp, atk, exp, gold, 0) {
}

void Monster::move(int dir) {
    if (frozen) {
        if (frozenDelay != DEBUF_FOREVER) {
            frozenDelay--;
            if (frozenDelay <= 0) {
                frozen = false;
            }
        }
        return;
    }

    if (stunned) {
        if (stunnedDelay != DEBUF_FOREVER) {
            stunnedDelay--;
            if (stunnedDelay <= 0) {
                stunned = false;
            }
        }
        //return;
    }
    
    if (isAlly) {
        if (isAllyDelay != DEBUF_FOREVER) {
            isAllyDelay--;
            if (isAllyDelay <= 0) {
                isAlly = false;
                unmorph();
            }
        }
        //return;
    }
    
    if (dir == DIR_NORTH) {
        if (board->validate(row-1, col) &&
            board->getUnit(row-1, col) == NULL &&
            board->isClimbable(row-1, col)) {
            board->removeUnit(row, col);
            board->setUnit(row-1, col, this);
        }
    }
    else if (dir == DIR_EAST) {
        if (board->validate(row, col+1) &&
            board->getUnit(row, col+1) == NULL &&
            board->isClimbable(row, col+1)) {
            board->removeUnit(row, col);
            board->setUnit(row, col+1, this);
        }
    }
    else if (dir == DIR_SOUTH) {
        if (board->validate(row+1, col) &&
            board->getUnit(row+1, col) == NULL &&
            board->isClimbable(row+1, col)) {
            board->removeUnit(row, col);
            board->setUnit(row+1, col, this);
        }
    }
    else if (dir == DIR_WEST) {
        if (board->validate(row, col-1) &&
            board->getUnit(row, col-1) == NULL &&
            board->isClimbable(row, col-1)) {
            board->removeUnit(row, col);
            board->setUnit(row, col-1, this);
        }
    }
}

bool Monster::useItem(int index) {
    // N/A
    return false;
}

bool Monster::isMonster() {
    return true;
}

void Monster::interact(Unit *unit) {
    //cout << "Hi!!" << endl;
    //cout << "Press any key.." << endl;
    //getchar();
 
    decHp(unit->getAtk());
    
    if (!isDead() && !stunned && !isAlly) {
        unit->decHp(getAtk());
    }  
}
