#include <iostream>

using namespace std;

#include "board.h"
#include "hero.h"

Hero::Hero() : Unit(DEFAULT_HERO_SHAPE, -1, -1, DEFAULT_HERO_MAX_HP, DEFAULT_HERO_HP,
					DEFAULT_HERO_MAX_MP, DEFAULT_HERO_MP, DEFAULT_HERO_ATK,
					DEFAULT_HERO_EXP, DEFAULT_HERO_GOLD, DEFAULT_HERO_SPEED/*, DEFAULT_HERO_HP*/) {
    slots = new Inventory(DEFAULT_HERO_SLOTS_CAPACITY);
}

Hero::Hero(char shape, int row, int col, int maxHp, int hp, int maxMp, int mp,
		   int atk, int exp, int gold, int slotsCapacity, int speed)
        : Unit(shape, row, col, maxHp, hp, maxMp, mp, atk, exp, gold, speed) {
    slots = new Inventory(slotsCapacity);
}

void Hero::printStat() {
    Unit::printStat();
    cout << endl;
    slots->print();
	cout << endl;
	cout << "Right Hand(";
	if (rightHand != NULL) {
		rightHand->print();
	}
	else {
		cout << " ";
	}
	cout << ")" << endl;

	if (unitEngaged != NULL) {
		unitEngaged->printStat();
		cout << endl;
	}
}

void Hero::move(int dir) {
	if (ride != NULL) {
		ride->move(dir);
		return;
	}
	
	bool moved = false;
	
	int nextRow = row;
	int nextCol = col;
	
    if (dir == DIR_NORTH) {
		nextRow = row-1;
    }
    else if (dir == DIR_EAST) {
		nextCol = col+1;
    }
    else if (dir == DIR_SOUTH) {
		nextRow = row+1;
    }
    else if (dir == DIR_WEST) {
		nextCol = col-1;
    }

	if (!board->validate(nextRow, nextCol)) {
		return;
	}

	// ë§Œì•½ì— ì›€ì§ì¼ ìž¥ì†Œì— ridable unitì´ ìžˆë‹¤ë©´, íƒ„ë‹¤.
	if (board->validate(nextRow, nextCol) &&
		board->getUnit(nextRow, nextCol) != NULL &&
		board->getUnit(nextRow, nextCol)->isRidable()) {
		ride = board->getUnit(nextRow, nextCol);
		ride->setHero(this);
		board->removeUnit(row, col); // heroë¥¼ ë•…ì—ì„œ ì§€ìš°ê¸°.
		board->removeUnit(ride->getRow(), ride->getCol()); // rideë¥¼ ë•…ì—ì„œ ì§€ìš°ê¸°.
		if (ride->isSkyUnit()) {
			board->setSkyUnit(ride->getRow(), ride->getCol(), ride); // í•˜ëŠ˜ì— ë„ìš°ê¸°.
		}
		else if (ride->isWaterUnit()) {
			board->setWaterUnit(ride->getRow(), ride->getCol(), ride); // ë¬¼ì— ë„ìš°ê¸°.
		}
		return;
	}

	// move!
	if (board->validate(nextRow, nextCol) &&
		board->getUnit(nextRow, nextCol) == NULL &&
		board->isClimbable(nextRow, nextCol) &&
		board->canLeave(row, col)) {
		board->removeUnit(row, col);
		board->setUnit(nextRow, nextCol, this);
		moved = true;
	}
	
	// pick up an item 
	if (moved) {
		if (board->getItem(row, col) != NULL && !slots->isFull()) {
			Item *itemPickedUp = board->removeItem(row, col);
			slots->insert(itemPickedUp);
		}
	}
	
	// interact with unit: battle!! or shopping!!
	if (!moved) {
		if (board->getUnit(nextRow, nextCol) != NULL) {
			if (board->getUnit(nextRow, nextCol)->isMonster()) {
				unitEngaged = board->getUnit(nextRow, nextCol);
			}
			board->getUnit(nextRow, nextCol)->interact(this);
		}
	}
}

bool Hero::useItem(int index) {
    return slots->useItemAt(index, this);
}

bool Hero::isHero() {
	return true;
}

void Hero::effect(Unit *unit, Item *item, Prop *prop, int skillNumber) {
	if (skillNumber == MAGIC_00_FIREWAVE) {
		if (unit != NULL && !unit->isHero()) {
			unit->decHp(MAGIC_00_FIREWAVE_ATK);
		}
	}
	else if (skillNumber == MAGIC_01_FREEZE) {
		if (unit != NULL) {
			unit->freeze(DEBUF_DELAY_FREEZE);
			unit->decHp(MAGIC_01_FREEZE_ATK);
		}
	}
	else if (skillNumber == MAGIC_02_STUN) {
		if (unit != NULL) {
			unit->stun(DEBUF_DELAY_STUN);
			unit->decHp(MAGIC_02_STUN_ATK);
		}
	}
	else if (skillNumber == MAGIC_03_ALLY) {
		if (unit != NULL) {
			unit->ally(DEBUF_DELAY_ALLY);
			unit->decHp(MAGIC_03_ALLY_ATK);
			unit->morph(DEFAULT_ALLY_SHAPE);
		}
	}
	else if (skillNumber == MAGIC_04_JUICE) {
		if (unit != NULL) {
			// ì—¬ê¸°ëŠ” ì–´ë””?
			//   - Hero::effect()
			// ë‚˜ëŠ” ëˆ„êµ¬?
			//   - hero
			// ë‚´ ìœ„ì¹˜ëŠ”?
			//   - Unit::row, col
			// ëˆ„êµ¬ë¥¼ handle? ëª¬ìŠ¤í„°?
			//   - ëª¬ìŠ¤í„°?
			//   - passë°›ì€ unitì´ isMonster()ì— trueë¥¼ returní•  ê²½ìš°..
			if (unit->isMonster()) {
				int poison = rand() % 2;
				if (poison == 0) {
					unit->decHp(DEFAULT_JUICE_HP);
				}
				else {
					unit->incHp(DEFAULT_JUICE_HP);
				}
			}
		}
	}	
}

void Hero::affectByTile() {	
	// check whether the hero is on Lava
	if (board->getBase(row, col)->isLava()) {
		decHp(2);
	}
}

void Hero::getOff() {
	// ë‚´ë¦´ë•ŒëŠ” ê·¸ íƒˆê²ƒì´ ë‚´ê°€ ë‚´ë ¤ë„ ë˜ëŠ”ì§€ ì²´í¬í•´ì„œ ë‚˜ë¥¼ kick outí•˜ëŠ” ê²ƒì´ë‹¤.
	if (ride != NULL) {
		if (ride->getOff(this)) {
			ride = NULL;
		}
	}
}

bool Hero::equip(Item *item) {
	if (rightHand != NULL) {
		return false;
	}
	
	rightHand = (Weapon *)item;
	atk += rightHand->getAtk();
	return true;
}

bool Hero::hasRoom() {
	return !slots->isFull();
}

// pre-condition: hasRoom() == true
void Hero::receiveItem(Item *item) {
	slots->insert(item);
}

//==============================================================================
// class AirBalloon
//==============================================================================

AirBalloon::AirBalloon()
: Unit(DEFAULT_AIR_BALLOON_SHAPE, -1, -1, 0, 0, 0, 0, 0, 0, 0, DEFAULT_AIR_BALLOON_SPEED) {
	hero = NULL;
}

AirBalloon::AirBalloon(char shape, int row, int col, int speed)
: Unit(shape, row, col, 0, 0, 0, 0, 0, 0, 0, speed) {
	hero = NULL;
}

void AirBalloon::printStat() {
	cout << "{";
	if (hero == NULL) {
		cout << " ";
	}
	else {
		hero->print();
	}
	cout << "}";
}

Hero *AirBalloon::getHero() {
	return hero;
}

void AirBalloon::setHero(Hero *hero) {
	this->hero = hero;
}

bool AirBalloon::isRidable() {
	return true;
}

bool AirBalloon::isSkyUnit() {
	return true;
}

bool AirBalloon::isAirBalloon() {
	return true;
}

bool AirBalloon::getOff(Unit *unit) {
	// ë‚˜ì¤‘ì— ì—¬ëŸ¬ëª…ì´ íƒ€ëŠ” ridableì¼ ê²½ìš°, unitì˜ arrayë¡œ passengerê°€ ìžˆê²Œ ëœë‹¤.
	// ì´ë•Œ ë‚´ë¦¬ê¸¸ ì›í•˜ëŠ” unitë§Œ ì°¾ì•„ì„œ ë‚´ë¦¬ê²Œ í•œë‹¤.
	if (hero != unit) {
		return false;
	}

	// ì¼ë‹¨ skyUnitì´ ëžœë”©ì´ ê°€ëŠ¥í•˜ì§€ í˜„ìž¬ ìžë¦¬ë¥¼ ì²´í¬í•˜ê³ ..
	if (board->validate(row, col) &&
		board->getUnit(row, col) == NULL && board->isClimbable(row, col)) {
		// ì£¼ë³€ì„ checkí•´ì„œ ë¹ˆìžë¦¬ì— unitì„ ë‚´ë¦°ë‹¤.
		for (int i = row-1; i <= row+1; i++) {
			for (int j = col-1; j <= col+1; j++) {
				if (!(i == row && j == col) && // AirBalloonìžë¦¬ëŠ” ëº€ë‹¤.
					board->validate(i, j) &&
					board->getUnit(i, j) == NULL && board->isClimbable(i, j)) {
					board->setSkyUnit(row, col, NULL); // í•˜ëŠ˜ì—ì„œ ë‚´ë ¤ì˜¤ê¸° ìœ„í•´..
					board->setUnit(row, col, this); // í•˜ëŠ˜ì—ì„œ ë‚´ë ¤ì˜¤ê¸° ìœ„í•´..
					board->setUnit(i, j, hero); // unitë‚´ë¦¬ê¸°.
					hero = NULL;
					return true;
				}
			}
		}
	}
	
	return false;
}

void AirBalloon::move(int dir) {
	bool moved = false;
	
	int nextRow = row;
	int nextCol = col;
	
	if (dir == DIR_NORTH) {
		nextRow = row-1;
	}
	else if (dir == DIR_EAST) {
		nextCol = col+1;
	}
	else if (dir == DIR_SOUTH) {
		nextRow = row+1;
	}
	else if (dir == DIR_WEST) {
		nextCol = col-1;
	}
	
	if (!board->validate(nextRow, nextCol)) {
		return;
	}
	
	// move!
	if (board->validate(nextRow, nextCol) &&
		board->getSkyUnit(nextRow, nextCol) == NULL) {
		board->setSkyUnit(row, col, NULL);
		board->setSkyUnit(nextRow, nextCol, this);
		moved = true;
	}
}

bool AirBalloon::useItem(int index) {
	// N/A
	return false;
}

//==============================================================================
// class Boat
//==============================================================================

Boat::Boat()
: Unit(DEFAULT_BOAT_SHAPE, -1, -1, 0, 0, 0, 0, 0, 0, 0, DEFAULT_BOAT_SPEED) {
	hero = NULL;
}

Boat::Boat(char shape, int row, int col, int speed)
: Unit(shape, row, col, 0, 0, 0, 0, 0, 0, 0, speed) {
	hero = NULL;
}

void Boat::printStat() {
	cout << "{";
	if (hero == NULL) {
		cout << " ";
	}
	else {
		hero->print();
	}
	cout << "}";
}

Hero *Boat::getHero() {
	return hero;
}

void Boat::setHero(Hero *hero) {
	this->hero = hero;
}

bool Boat::isRidable() {
/*	if (row, col = '~'){
		return true;
	}
	else {
		return false;
	}
*/
	return true;
}

bool Boat::isWaterUnit() {
	return true;
}

bool Boat::isBoat() {
	return true;
}

bool Boat::getOff(Unit *unit) {
	if (hero != unit) {
		return false;
	}
	
	if (board->validate(row, col) &&
		board->getUnit(row, col) == NULL && board->isClimbable(row, col)) {
		for (int i = row-1; i <= row+1; i++) {
			for (int j = col-1; j <= col+1; j++) {
				if (!(i == row && j == col) && 
					board->validate(i, j) &&
					board->getUnit(i, j) == NULL && board->isClimbable(i, j)) {
					board->setWaterUnit(row, col, NULL);
					board->setUnit(row, col, this);
					board->setUnit(i, j, hero);
					hero = NULL;
					return true;
				}
			}
		}
	}
	
	return false;
}

void Boat::move(int dir) {
	bool moved = false;
	
	int nextRow = row;
	int nextCol = col;
	
	if (dir == DIR_NORTH) {
		nextRow = row-1;
	}
	else if (dir == DIR_EAST) {
		nextCol = col+1;
	}
	else if (dir == DIR_SOUTH) {
		nextRow = row+1;
	}
	else if (dir == DIR_WEST) {
		nextCol = col-1;
	}
	
	if (!board->validate(nextRow, nextCol)) {
		return;
	}
	
	// move!
	if (board->validate(nextRow, nextCol) &&
		board->isOnWater(nextRow, nextCol) &&
		board->getWaterUnit(nextRow, nextCol) == NULL) {
		board->setWaterUnit(row, col, NULL);
		board->setWaterUnit(nextRow, nextCol, this);
		moved = true;
	}
}

bool Boat::useItem(int index) {
	// N/A
	return false;
}
