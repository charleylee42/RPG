#include <iostream>

using namespace std;

#include "tile.h"

Tile::Tile() {
    speedCounter = 0;
    
    cursor = NULL;

    fx = FX_NONE;
    
    skyUnit = NULL;
    waterUnit = NULL;
    unit = NULL;
    prop = NULL;
    item = NULL;
    base = NULL;
}

// print ë¥˜
void Tile::print() {
    if (cursor != NULL) {
        cursor->print();
    }
    
    else if (fx != FX_NONE) {
        cout << fx;
    }
    else if (skyUnit != NULL) {
        skyUnit->print();
    }
    else if (waterUnit != NULL) {
        waterUnit->print();
    }
    else if (unit != NULL) {
        unit->print();
    }
    else if (item != NULL) {
        item->print();
    }
    else if (prop != NULL) {
        prop->print();
    }
    else { //if (base != NULL) {
        base->print();
    }
    //else {
    //    cout << TILE_EMPTY;
    //}
}

char Tile::getFx() {
    return fx;
}

void Tile::setFx(char fx) {
    this->fx = fx;
}

void Tile::clearFx() {
    fx = FX_NONE;
}

Cursor *Tile::getCursor() {
    return cursor;
}

void Tile::setCursor(Cursor *cursor) {
    this->cursor = cursor;
}

Unit *Tile::getSkyUnit() {
    return skyUnit;
}

void Tile::setSkyUnit(Unit *skyUnit) {
    this->skyUnit = skyUnit;
}

Unit *Tile::getWaterUnit() {
    return waterUnit;
}

void Tile::setWaterUnit(Unit *waterUnit) {
    this->waterUnit = waterUnit;
}

Unit *Tile::getUnit() {
    return unit;
}

void Tile::setUnit(Unit *unit) {
    this->unit = unit;
}

Prop *Tile::getProp() {
    return prop;
}

void Tile::setProp(Prop *prop) {
    this->prop = prop;
}

Item *Tile::getItem() {
    return item;
}

void Tile::setItem(Item *item) {
    this->item = item;
}

Base *Tile::getBase() {
    return base;
}

void Tile::setBase(Base *base) {
    speedCounter = base->getSpeed();
    this->base = base;
}

bool Tile::isOnWater() {
    return base != NULL && base->isWater();
}

bool Tile::canLeave() {
    if (speedCounter == 0) {
        if (base != NULL) {
            speedCounter = base->getSpeed();
        }
        return true;
    }
    else {
        speedCounter--;
        return false;
    }
}
