#ifndef BOARD_H
#define BOARD_H

#include "main.h"
#include "unit.h"
#include "hero.h"
#include "monster.h"
#include "merchant.h"
#include "shockwave.h"
#include "tile.h"

class Board {
protected:
    Tile ***board;
    int rowSize;
    int colSize;
    
    Monster **mons;
    int numMons;
    int maxNumMons;
   
    Merchant **merchants;
    int numMerchants;
    int maxNumMerchants;
    
    Unit **skyUnits;
    int numSkyUnits;
    int maxNumSkyUnits;
    
    Unit **waterUnits;
    int numWaterUnits;
    int maxNumWaterUnits;
    
    Hero *hero;
    
    // for shockwave
    Shockwave **shockwaves;
    int maxNumShockwaves;
    int numShockwaves;

    // private helper function
    void initMons(int maxNumMons);
    void initMerchants(int maxNumMerchants);
    void initSkyUnits(int maxNumSkyUnits);
    void initWaterUnits(int maxNumWaterUnits);
    void initPotions(int maxNumPotions);
    void initFx();

public:
    Board();
    Board(int levelNum);
    ~Board();
    
    void print();
    void print(char **editModeLayer); // print() for edit mode

    void clearFx(int row, int col);
    void setFx(int row, int col, char fx);
    void startWave(Unit *waveUnit, Item *waveItem, Prop *waveProp,
                   int row, int col, int range, int frameInterval, char fxShape, int skillNumber);

    int getRowSize();
    int getColSize();

    bool validate(int row, int col);
    bool isClimbable(int row, int col);

    Cursor *getCursor(int row, int col);
    void setCursor(int row, int col, Cursor *cursor);

    Unit *getSkyUnit(int row, int col);
    void setSkyUnit(int row, int col, Unit *skyUnit);
    
    Unit *getWaterUnit(int row, int col);
    void setWaterUnit(int row, int col, Unit *waterUnit);

    Unit *getUnit(int row, int col);
    void setUnit(int row, int col, Unit *unit);
    
    Item *getItem(int row, int col);
    Item *removeItem(int row, int col);

    Prop *getProp(int row, int col);
    void setProp(int row, int col, Prop *prop);

    bool isOnWater(int row, int col);

    Base *getBase(int row, int col);

    Hero *getHero();
    
    //bool isEmpty(int row, int col);
    Unit *removeUnit(int row, int col);
    
    void moveMons();
    
    bool canLeave(int row, int col);
};

#endif
