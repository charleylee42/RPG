#include <iostream>

using namespace std;

#include "board.h"
#include "hero.h"
#include "levels.h"

Board::Board() {
#ifdef DEBUG_MSG
    cout << "Board::Board(): started!!" << endl;
#endif
    rowSize = DEFAULT_ROW_SIZE;
    colSize = DEFAULT_COL_SIZE;
    
    board = new Tile **[rowSize];
    
    // create 1D array of Tile * for each row. 
    for (int i = 0; i < rowSize; i++) {
        board[i] = new Tile *[colSize];
    }
    
    // create Tile objects
    for (int i = 0; i < rowSize; i++) {
        for (int j = 0; j < colSize; j++) {
            board[i][j] = new Tile();
        }
    }
    
    hero = new Hero();
    setUnit(DEFAULT_ROW_SIZE / 2, DEFAULT_COL_SIZE / 2, hero);
    hero->setBoard(this);

    // init tree
    for (int i = 0; i < MAX_NUM_TREES; i++) {
        while (true) {
            int randRow = rand() % rowSize;
            int randCol = rand() % colSize;
            
            if (board[randRow][randCol]->getProp() == NULL) {
                board[randRow][randCol]->setProp(new Tree());
                break;
            }
        }
    }
    
    maxNumMons = DEFAULT_MAX_NUM_MONS;
    numMons = 0;
    initMons(maxNumMons);

    maxNumMerchants = DEFAULT_MAX_NUM_MERCHANTS;
    numMerchants = 0;
    initMerchants(numMerchants);
    
    maxNumSkyUnits = DEFAULT_MAX_NUM_BALLOONS;
    numSkyUnits = 0;
    initSkyUnits(maxNumSkyUnits);    
    
    maxNumWaterUnits = DEFAULT_MAX_NUM_BOATS;
    numWaterUnits = 0;
    initWaterUnits(maxNumWaterUnits);

    initPotions(MAX_NUM_ITEMS);
    
    initFx();

#ifdef DEBUG_MSG
    cout << "Board::Board(): ended!!" << endl;
#endif
}

Board::Board(int levelNum) {
    rowSize = ROW_SIZE;
    colSize = COL_SIZE;
    
    board = new Tile **[rowSize];
    
    // create 1D array of Tile * for each row. 
    for (int i = 0; i < rowSize; i++) {
        board[i] = new Tile *[colSize];
    }
    
    // create Tile objects
    for (int i = 0; i < rowSize; i++) {
        for (int j = 0; j < colSize; j++) {
            board[i][j] = new Tile();
            board[i][j]->setBase(new Base(levels[levelNum][i][j]));
        }
    }

/*
 #define DEFAULT_HERO_SHAPE 'H'
 #define DEFAULT_MONSTER_SHAPE 'm'
 #define DEFAULT_POTION_SHAPE 'b'
 #define DEFAULT_TREE_SHAPE 'T'
*/
    // count number of monsters
    maxNumMons = 0;
    maxNumSkyUnits = 0;
    maxNumWaterUnits = 0;
    maxNumMerchants = 0;

    for (int i = 0; i < rowSize; i++) {
        for (int j = 0; j < colSize; j++) {
            if (contents[levelNum][i][j] == DEFAULT_MONSTER_SHAPE) {
                maxNumMons++;
            }
            if (contents[levelNum][i][j] == DEFAULT_AIR_BALLOON_SHAPE) {
                maxNumSkyUnits++;
            }
            if (contents[levelNum][i][j] == DEFAULT_BOAT_SHAPE) {
                maxNumWaterUnits++;
            }
            if (contents[levelNum][i][j] == DEFAULT_MERCHANT_SHAPE) {
                maxNumMerchants++;
            }
        }
    }
            
    mons = new Monster *[maxNumMons];
    numMons = 0;

    skyUnits = new Unit *[maxNumSkyUnits];
    numSkyUnits = 0;
    
    waterUnits = new Unit *[maxNumWaterUnits];
    numWaterUnits = 0;

    merchants = new Merchant *[maxNumMerchants];
    numMerchants = 0;

    // Place objects
    for (int i = 0; i < rowSize; i++) {
        for (int j = 0; j < colSize; j++) {
            if (contents[levelNum][i][j] == DEFAULT_HERO_SHAPE) {
                hero = new Hero();
                setUnit(i, i, hero);
                hero->setBoard(this);
            }
            else if (contents[levelNum][i][j] == DEFAULT_MONSTER_SHAPE) {
                mons[numMons] = new Monster();
                mons[numMons]->setBoard(this);
                setUnit(i, j, mons[numMons]);
                numMons++;
            }
            else if (contents[levelNum][i][j] == DEFAULT_MERCHANT_SHAPE) {
                merchants[numMerchants] = new Merchant();
                merchants[numMerchants]->setBoard(this);
                setUnit(i, j, merchants[numMerchants]);
                numMerchants++;
            }
            else if (contents[levelNum][i][j] == DEFAULT_AIR_BALLOON_SHAPE) {
                skyUnits[numSkyUnits] = new AirBalloon();
                skyUnits[numSkyUnits]->setBoard(this);
                setUnit(i, j, skyUnits[numSkyUnits]);
                numSkyUnits++;
            }
            else if (contents[levelNum][i][j] == DEFAULT_BOAT_SHAPE) {
                    waterUnits[numWaterUnits] = new Boat();
                    waterUnits[numWaterUnits]->setBoard(this);
                    setUnit(i, j, waterUnits[numWaterUnits]);
                    numWaterUnits++;
            }
            else if (contents[levelNum][i][j] == DEFAULT_POTION_SHAPE) {
                board[i][j]->setItem(new Potion());
            }
            else if (contents[levelNum][i][j] == DEFAULT_CHEST_SHAPE) {
                board[i][j]->setProp(new Chest());
            }
            else if (contents[levelNum][i][j] == DEFAULT_TREE_SHAPE) {
                board[i][j]->setProp(new Tree());
            }
            else if (contents[levelNum][i][j] == DEFAULT_BREAD_SHAPE) {
                board[i][j]->setItem(new Bread());
            }
            else if (isWeapon(contents[levelNum][i][j])) {
                board[i][j]->setItem(createRandomWeaponByShape(contents[levelNum][i][j]));
            }
            else if (isArmor(contents[levelNum][i][j])) {
                board[i][j]->setItem(createRandomArmorByShape(contents[levelNum][i][j]));
            }
        }
    }

    initFx();
}

void Board::initMons(int maxNumMons) {
    mons = new Monster *[maxNumMons];
    
    // create objects of Monster for each slot
    for (int i = 0; i < maxNumMons; i++) {
        mons[i] = new Monster();
        mons[i]->setBoard(this);
        
        // put the current monster on a random coord.
        while (true) {
            int randRow = rand() % rowSize;
            int randCol = rand() % colSize;
            
            if (board[randRow][randCol]->getProp() == NULL &&
                board[randRow][randCol]->getUnit() == NULL) {
                mons[i]->setRow(randRow);
                mons[i]->setCol(randCol);
                board[randRow][randCol]->setUnit(mons[i]);
                break;
            }
        }
        numMons++;
    }
}
void Board::initMerchants(int maxNumMerchants) {
    merchants = new Merchant *[maxNumMerchants];
    
    // create objects of Monster for each slot
    for (int i = 0; i < maxNumMons; i++) {
        merchants[i] = new Merchant();
        merchants[i]->setBoard(this);
        
        // put the current monster on a random coord.
        while (true) {
            int randRow = rand() % rowSize;
            int randCol = rand() % colSize;
            
            if (board[randRow][randCol]->getProp() == NULL &&
                board[randRow][randCol]->getUnit() == NULL) {
                merchants[i]->setRow(randRow);
                merchants[i]->setCol(randCol);
                board[randRow][randCol]->setUnit(merchants[i]);
                break;
            }
        }
        numMerchants++;
    }
}

void Board::initSkyUnits(int maxNumSkyUnits) {
    skyUnits = new Unit *[maxNumSkyUnits];
    
    // create objects of Sky Unit for each slot
    for (int i = 0; i < maxNumSkyUnits; i++) {
        skyUnits[i] = new AirBalloon ();
        skyUnits[i]->setBoard(this);
        
        // put the current monster on a random coord.
        while (true) {
            int randRow = rand() % rowSize;
            int randCol = rand() % colSize;
            
            if (board[randRow][randCol]->getProp() == NULL &&
                board[randRow][randCol]->getUnit() == NULL) {
                skyUnits[i]->setRow(randRow);
                skyUnits[i]->setCol(randCol);
                board[randRow][randCol]->setUnit(skyUnits[i]);
                break;
            }
        }
        numSkyUnits++;
    }
}
void Board::initWaterUnits(int maxNumWaterUnits) {
    waterUnits = new Unit *[maxNumWaterUnits];
    
    // create objects of Sky Unit for each slot
    for (int i = 0; i < maxNumWaterUnits; i++) {
        waterUnits[i] = new Boat ();
        waterUnits[i]->setBoard(this);
        
        // put the current monster on a random coord.
        while (true) {
            int randRow = rand() % rowSize;
            int randCol = rand() % colSize;
            
            if (board[randRow][randCol]->getProp() == NULL &&
                board[randRow][randCol]->getUnit() == NULL) {
                waterUnits[i]->setRow(randRow);
                waterUnits[i]->setCol(randCol);
                board[randRow][randCol]->setUnit(waterUnits[i]);
                break;
            }
        }
        numWaterUnits++;
    }
}

void Board::initPotions(int maxNumPotions) {
    // create objects of Potion
    for (int i = 0; i < maxNumPotions; i++) {
        // put the current potion on a random coord.
        while (true) {
            int randRow = rand() % rowSize;
            int randCol = rand() % colSize;
            
            if (board[randRow][randCol]->getItem() == NULL &&
                board[randRow][randCol]->getProp() == NULL) {
                board[randRow][randCol]->setItem(new Potion());
                break;
            }
        }
    }
}

void Board::initFx() {
    maxNumShockwaves = MAX_NUM_SHOCKWAVES;
    shockwaves = new Shockwave *[maxNumShockwaves];
    numShockwaves = 0;
    
    for (int i = 0; i < maxNumShockwaves; i++) {
        shockwaves[i] = NULL;
    }
}

Board::~Board() {
#ifdef DEBUG_MSG
    cout << "Board::~Board(): started!!" << endl;
#endif
    // create Tile objects
    for (int i = 0; i < rowSize; i++) {
        for (int j = 0; j < colSize; j++) {
            delete board[i][j];
        }
    }
    
    // create 1D array of Tile * for each row. 
    for (int i = 0; i < rowSize; i++) {
        delete [] board[i];
    }
    
    delete [] board;
#ifdef DEBUG_MSG
    cout << "Board::~Board(): ended!!" << endl;
#endif
}

void Board::print() {
    // process all shockwaves --------------------------------------------------
    for (int i = 0; i < maxNumShockwaves; i++) {
        if (shockwaves[i] != NULL) {
            if (!shockwaves[i]->getWaveActivated()) {
                delete shockwaves[i];
                shockwaves[i] = NULL;
                numShockwaves--;
            }
            else {
                shockwaves[i]->print();
            }
        }
    }
    // process all shockwaves end ----------------------------------------------

    for (int i = 0; i < rowSize; i++) {
        for (int j = 0; j < colSize; j++) {
            board[i][j]->print();
        }
        cout << endl;
    }
}

void Board::print(char **editModeLayer) {
    for (int i = 0; i < rowSize; i++) {
        for (int j = 0; j < colSize; j++) {
            if (editModeLayer[i][j] != EDIT_MODE_EMPTY_SHAPE) {
                cout << editModeLayer[i][j];
            }
            else {
                board[i][j]->print();
            }
        }
        cout << endl;
    }
}

void Board::clearFx(int row, int col) {
    board[row][col]->clearFx();
}

void Board::setFx(int row, int col, char fx) {
    board[row][col]->setFx(fx);
}

void Board::startWave(Unit *waveUnit, Item *waveItem, Prop *waveProp,
                      int row, int col, int range, int frameInterval, char fxShape, int skillNumber) {
    if (numShockwaves >= maxNumShockwaves) {
        cout << "error: can't start new shockwave!";
        return;
    }
    
    for (int i = 0; i < maxNumShockwaves; i++) {
        if (shockwaves[i] == NULL) {
            shockwaves[i] = new Shockwave(waveUnit, waveItem, waveProp,
                                          row, col, range, frameInterval, fxShape);
            shockwaves[i]->setBoard(this);
            shockwaves[i]->start();
            shockwaves[i]->setSkillNumber(skillNumber);
            numShockwaves++;
            break;
        }
    }
}

int Board::getRowSize() {
    return rowSize;
}

int Board::getColSize() {
    return colSize;
}

bool Board::validate(int row, int col) {
    return row >= 0 && row < rowSize && col >= 0 && col < colSize;
}

bool Board::isClimbable(int row, int col) {
    return
        (board[row][col]->getProp() == NULL ||
         board[row][col]->getProp()->isClimbable()) && 
        board[row][col]->getBase()->isClimbable();
}

Cursor *Board::getCursor(int row, int col) {
    return board[row][col]->getCursor();
}

void Board::setCursor(int row, int col, Cursor *cursor) {
    board[row][col]->setCursor(cursor);
    if (cursor != NULL) {
        cursor->setRow(row);
        cursor->setCol(col);
    }
}

Unit *Board::getSkyUnit(int row, int col) {
    return board[row][col]->getSkyUnit();
}

void Board::setSkyUnit(int row, int col, Unit *skyUnit) {
    board[row][col]->setSkyUnit(skyUnit);
    if (skyUnit != NULL) {
        skyUnit->setRow(row);
        skyUnit->setCol(col);
    }
}

Unit *Board::getWaterUnit(int row, int col) {
    return board[row][col]->getWaterUnit();
}

void Board::setWaterUnit(int row, int col, Unit *waterUnit) {
    board[row][col]->setWaterUnit(waterUnit);
    if (waterUnit != NULL) {
        waterUnit->setRow(row);
        waterUnit->setCol(col);
    }
}

Unit *Board::getUnit(int row, int col) {
    return board[row][col]->getUnit();
}

void Board::setUnit(int row, int col, Unit *unit) {
    board[row][col]->setUnit(unit);
    if (unit != NULL) {
        unit->setRow(row);
        unit->setCol(col);
    }
}

Item *Board::getItem(int row, int col) {
    if (!validate(row, col)) {
        return NULL;
    }
    
    return board[row][col]->getItem();
}

Prop *Board::getProp(int row, int col) {
    if (!validate(row, col)) {
        return NULL;
    }
    
    return board[row][col]->getProp();
}

void Board::setProp(int row, int col, Prop *prop) {
    if (!validate(row, col)) {
        return;
    }

    board[row][col]->setProp(prop);
}

bool Board::isOnWater(int row, int col) {
    if (!validate(row, col)) {
        return false;
    }
    
    return board[row][col]->isOnWater();
}

Item *Board::removeItem(int row, int col) {
    if (!validate(row, col)) {
        return NULL;
    }

    Item *itemToReturn = board[row][col]->getItem();
    board[row][col]->setItem(NULL);
    return itemToReturn;
}

Hero *Board::getHero() {
    return hero;
}

/*
bool Board::isEmpty(int row, int col) {
    if (!validate(row, col)) {
        return false;
    }
    return  board[row][col]->getProp() == NULL &&
            (board[row][col]->getUnit() == NULL ||
             board[row][col]->getUnit()->isRidable()) &&
            board[row][col]->getBase()->isClimbable();
}
*/

Unit *Board::removeUnit(int row, int col) {
    if (!validate(row, col)) {
        return NULL;
    }
    Unit *unitToReturn = board[row][col]->getUnit();
    board[row][col]->setUnit(NULL);
    return unitToReturn;
}

Base *Board::getBase(int row, int col) {
    if (!validate(row, col)) {
        return NULL;
    }
    return board[row][col]->getBase();
}

void Board::moveMons() {
    for (int i = 0; i < numMons; i++) {
        if (mons[i]->isDead() && mons[i]->getRow() != -1) {
            setUnit(mons[i]->getRow(), mons[i]->getCol(), NULL);
            mons[i]->setRow(-1);
            mons[i]->setCol(-1);
        }
        else if (!mons[i]->isDead()) {
            // decide random direction
            int randDir = rand() % NUM_DIRECTIONS;
            mons[i]->move(randDir);
        }
    }
}

bool Board::canLeave(int row, int col) {
    if (!validate(row, col)) {
        return NULL;
    }
    return board[row][col]->canLeave();
}
