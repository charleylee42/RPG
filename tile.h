#ifndef TILE_H
#define TILE_H

#include "main.h"
#include "item.h"
#include "prop.h"
#include "unit.h"
#include "cursor.h"
#include "base.h"
#include "fx.h"

#define FX_NONE '\0'
class Tile {
protected:
    
    int speedCounter;
    
    char fx;
    Cursor *cursor;
    
    Unit *skyUnit;
    Unit *waterUnit;
    Unit *unit;
    Item *item;
    Prop *prop;
    Base *base; // ex) water, snow, sand
     
public:
    Tile();
    
    void print();
    
    char getFx();
    void setFx(char fx);
    void clearFx(); // resteFx()

    Cursor *getCursor();
    void setCursor(Cursor *cursor);
    Unit *getSkyUnit();
    void setSkyUnit(Unit *skyUnit);
    Unit *getWaterUnit();
    void setWaterUnit(Unit *waterUnit);
    Unit *getUnit();
    void setUnit(Unit *unit);    
    Prop *getProp();
    void setProp(Prop *prop);    
    Item *getItem();
    void setItem(Item *item);
    Base *getBase();
    void setBase(Base *base);
    
    bool isOnWater();
    
    bool canLeave();
};

#endif
