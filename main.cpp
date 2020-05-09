#include <iostream>
#include <fstream>
#include <stdlib.h>     // srand, rand
#include <time.h>       // time 

#ifdef VISUAL_STUDIO
#include <windows.h>
#include <conio.h>
#endif

#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

int _kbhit(void)
{
    struct termios oldt, newt;
    int ch;
    int oldf;
    
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
    
    ch = getchar();
    
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    
    if(ch != EOF)
    {
        ungetc(ch, stdin);
        return 1;
    }
    
    return 0;
}

using namespace std;

#include "main.h"
#include "item.h"
#include "unit.h"
#include "hero.h"
#include "tile.h"
#include "board.h"
#include "levels.h"

// global variable
int gWorldTime = 0;

#include "item.h"

int main(int argc, const char * argv[]) {

//    Inventory *inv = new Inventory();
//    
//    for (int i = 0; i < 5; i++) {
//        inv->insert(createRandomItem());
//    }
//    
////    for (int i = 0; i < 5; i++) {
////        inv->getItemAt(i)->printFullSpec();
////        cout << endl;
////    }
//    
//    inv->resetIterator();
//    
//    while (inv->hasMore()) {
//        Item *item = inv->next();
//        
//        if (item != NULL) {
//            item->printFullSpec();
//            cout << endl;
//
//        }
//        else {
//            cout << "EMPTY" << endl;
//        }
//    }
//    
    
//    for (int i = 0; i < 10; i++) {
//        Armor *a1 = createRandomArmor();
//        a1->printFullSpec();
//        cout << endl;
//    }
//    cout << endl;
//
//    for (int i = 0; i < 10; i++) {
//        Weapon *w1 = createRandomWeapon();
//        w1->printFullSpec();
//        cout << endl;
//    }
//    cout << endl;

//    for (int i = 0; i < 10; i++) {
//        Item *item = createRandomItem();
//        item->printFullSpec();
//        cout << endl;
//    }
//    cout << endl;
//
//    exit(1);
    
    srand((unsigned)time(NULL));
    
    //Board *board = new Board();
        // first step  : "new Board" -> create an object of class Board
        // second step : "Board()"   -> calling default constructor of the new Board object.
    int curLevel = CURRENT_LEVEL_TO_LOAD;
    Board *board = new Board(curLevel);
    
    Hero *hero = NULL;

    //--------------------------------------------------------------------------
    // Edit Mode: extra íŒë•Œê¸° ì¤€ë¹„ ë. unit, item, and propì„ ëŒì•„ëŒ•ê¸°ë©´ì„œ ë†“ì„ íŒë•Œê¸°.
    //            ëë‚œ í›„, saveí•˜ë©´, levels.cppì˜ arrayì²˜ëŸ¼ ìƒê¸´ ê²ƒì„ ìžë™ìœ¼ë¡œ saveí•´ì£¼ë„ë¡..
    //--------------------------------------------------------------------------
    char command;
    cout << "Edit mode? (y/N) : ";
    cin >> command;
    
    bool editMode = false;
    char **unitItemPropLayer = NULL;

    Cursor *cursor = NULL;

    int numHero = 0;

    // Edit Mode:
    if (command == 'y' || command == 'Y') {
        editMode = true;

        cursor = new Cursor();
        board->setCursor(startPos[0][curLevel], startPos[1][curLevel], cursor);
        cursor->setBoard(board);

        cout << "board->getRowSize(): " << board->getRowSize() << endl;
        cout << "board->getColSize(): " << board->getColSize() << endl;
        
        unitItemPropLayer = new char *[board->getRowSize()];
        
        for (int i = 0; i < board->getRowSize(); i++) {
            unitItemPropLayer[i] = new char[board->getColSize() + 1];
        }
        
        for (int i = 0; i < board->getRowSize(); i++) {
            for (int j = 0; j < board->getColSize(); j++) {
                unitItemPropLayer[i][j] = EDIT_MODE_EMPTY_SHAPE;
            }
            // ë§ˆì§€ë§‰ì— ê¼­ null charë¥¼ ë„£ì–´ì„œ ë‚˜ì¤‘ì— saveí•  ë•Œ ì—ëŸ¬ê°€ ì—†ë„ë¡ í•œë‹¤.
            unitItemPropLayer[i][board->getColSize()] = '\0';
        }
    }
    // Playing Mode:
    else {
    }
    
    hero = board->getHero();
    
    //--------------------------------------------------------------------------
    
    board->print();
    
    while (true) {
        //----------------------------------------------------------------------
        //----------------------------------------------------------------------
        //----------------------------------------------------------------------
        // edit mode
        //----------------------------------------------------------------------
        //----------------------------------------------------------------------
        //----------------------------------------------------------------------
        if (editMode) {
            int cursorDir = -1;

            char dirChar = '\0';
            
            // check whether the user wants to move the hero or not.
            if (_kbhit()) {
                dirChar = getchar();
                cout << endl;

                if (dirChar == DIR_NORTH_CHAR) {
                    cursorDir = DIR_NORTH;
                }
                else if (dirChar == DIR_EAST_CHAR) {
                    cursorDir = DIR_EAST;
                }
                else if (dirChar == DIR_SOUTH_CHAR) {
                    cursorDir = DIR_SOUTH;
                }
                else if (dirChar == DIR_WEST_CHAR) {
                    cursorDir = DIR_WEST;
                }
                else if (dirChar == 'q') {
                    string filename;
                    cout << "Enter the filename(-1 to cancel): ";
                    cin >> filename;
                    
                    if (filename != "-1") {
                        ofstream fout;
                        fout.open(filename.c_str());
                        
                        if (fout.fail()) {
                            cout << "error: Invalid filename!! Press any key to continue!" << endl;
                            while (!_kbhit()) {
                            }
                        }
                        else {
                            fout << "// curLevel: " << curLevel << endl;
                            fout << "{" << endl;
                            for (int i = 0; i < board->getRowSize(); i++) {
                                if (i != board->getRowSize()-1) {
                                    fout << "    \"" << unitItemPropLayer[i] << "\"," << endl;
                                }
                                else {
                                    fout << "    \"" << unitItemPropLayer[i] << "\"" << endl;
                                }
                            }
                            fout << "}" << endl;
                            
                            fout.close();
                        }
                    }
                }
                else {
                    bool validShape = false;
                    
                    for (int i = 0; i < strlen(UNIT_SHAPES) && !validShape; i++) {
                        if (dirChar == UNIT_SHAPES[i]) {
                            validShape = true;
                        }
                    }
                    for (int i = 0; i < strlen(PROP_SHAPES) && !validShape; i++) {
                        if (dirChar == PROP_SHAPES[i]) {
                            validShape = true;
                        }
                    }
                    for (int i = 0; i < strlen(ITEM_SHAPES) && !validShape; i++) {
                        if (dirChar == ITEM_SHAPES[i]) {
                            validShape = true;
                        }
                    }
                    if (!validShape && dirChar == EDIT_MODE_EMPTY_SHAPE) {
                        validShape = true;
                    }
                    
                    if (validShape) {
                        if (board->isClimbable(cursor->getRow(), cursor->getCol())) {
                            if (dirChar == DEFAULT_HERO_SHAPE) {
                                if (numHero <= 0) {
                                    unitItemPropLayer[cursor->getRow()][cursor->getCol()] = dirChar;
                                    numHero++;
                                }
                            }
                            else if (dirChar == EDIT_MODE_EMPTY_SHAPE) {
                                if (unitItemPropLayer[cursor->getRow()][cursor->getCol()] == DEFAULT_HERO_SHAPE) {
                                    numHero--;
                                }
                                unitItemPropLayer[cursor->getRow()][cursor->getCol()] = dirChar;
                            }
                            else {
                                unitItemPropLayer[cursor->getRow()][cursor->getCol()] = dirChar;
                            }
                        }
                    }
                }
                
                cursor->move(cursorDir);
            }
            
            cout << "=======================================================" << endl;
            board->print(unitItemPropLayer);
            cout << "Cursor  : (" << cursor->getRow() << ", " << cursor->getCol() << ")" << endl;
            cout << "Control :           (w) north" << endl;
            cout << "          (a) west  (s) south  (d) east" << endl;
            cout << "Command [ (q) save  (.) remove  (H) hero  (m) monster  (T) tree  (b) potion (F) flower (B) bread]" << endl;
        } // end of edit mode.
        //----------------------------------------------------------------------
        //----------------------------------------------------------------------
        //----------------------------------------------------------------------
        // playing mode
        //----------------------------------------------------------------------
        //----------------------------------------------------------------------
        //----------------------------------------------------------------------
        else {
            if (gWorldTime % (10 - hero->getSpeed() * 2)) {
                //------------------------------------------------------------------
                // handling "move"
                //------------------------------------------------------------------
                int heroDir = -1;
#ifdef HERO_RANDOM_MOVE
                heroDir = rand() % NUM_DIRECTIONS;
#else
                char dirChar = '\0';
                
                // check whether the user wants to move the hero or not.
#ifdef HERO_KEYBOARD_NO_ENTER_MOVE
                if (_kbhit()) {
                    dirChar = getchar();
                    cout << endl;
                }
#else
                cin >> dirChar;
#endif
                if (dirChar == DIR_NORTH_CHAR) {
                    heroDir = DIR_NORTH;
                }
                else if (dirChar == DIR_EAST_CHAR) {
                    heroDir = DIR_EAST;
                }
                else if (dirChar == DIR_SOUTH_CHAR) {
                    heroDir = DIR_SOUTH;
                }
                else if (dirChar == DIR_WEST_CHAR) {
                    heroDir = DIR_WEST;
                }
#endif
                if (heroDir != -1) {
                    hero->move(heroDir);
                }
                
                //------------------------------------------------------------------
                // handling magic
                
                //------------------------------------------------------------------
                if (dirChar == 'z') {
                    board->startWave(hero, NULL, NULL,
                                          hero->getRow(), hero->getCol(),
                                          HERO_POSTIONING_WAVE_RANGE,
                                          HERO_POSTIONING_WAVE_FRAME_INTERVAL,
                                          HERO_POSTIONING_WAVE_SHAPE,
                                          MAGIC_00_FIREWAVE);
                }
                if (dirChar == 'x') {
                    board->startWave(hero, NULL, NULL,
                                     hero->getRow(), hero->getCol(),
                                     HERO_POSTIONING_WAVE_RANGE,
                                     HERO_POSTIONING_WAVE_FRAME_INTERVAL,
                                     HERO_POSTIONING_WAVE_SHAPE,
                                     MAGIC_01_FREEZE);
                }
                if (dirChar == 'c') {
                    board->startWave(hero, NULL, NULL,
                                     hero->getRow(), hero->getCol(),
                                     HERO_POSTIONING_WAVE_RANGE,
                                     HERO_POSTIONING_WAVE_FRAME_INTERVAL,
                                     HERO_POSTIONING_WAVE_SHAPE,
                                     MAGIC_02_STUN);
                }
                if (dirChar == 'v') {
                    board->startWave(hero, NULL, NULL,
                                     hero->getRow(), hero->getCol(),
                                     HERO_POSTIONING_WAVE_RANGE,
                                     HERO_POSTIONING_WAVE_FRAME_INTERVAL,
                                     HERO_POSTIONING_WAVE_SHAPE,
                                     MAGIC_03_ALLY);
                }
                if (dirChar == 'j') {
                    board->startWave(hero, NULL, NULL,
                                     hero->getRow(), hero->getCol(),
                                     HERO_POSTIONING_WAVE_RANGE,
                                     HERO_POSTIONING_WAVE_FRAME_INTERVAL,
                                     HERO_POSTIONING_WAVE_SHAPE,
                                     MAGIC_04_JUICE);
                }
                
                //------------------------------------------------------------------
                // handling use
                //------------------------------------------------------------------
                // check whether the user wants to use an item from slots or not.
                if (dirChar >= '1' && dirChar <= ('1'+(DEFAULT_HERO_SLOTS_CAPACITY-1))) {
                    hero->useItem(dirChar-'1');
                }

                //------------------------------------------------------------------
                // handling "get off"
                //------------------------------------------------------------------
                if (dirChar == '0') {
                    hero->getOff();
                }
            }
            //------------------------------------------------------------------
            if (gWorldTime % 100 == 0) {
                board->moveMons();
            }
            
            if (gWorldTime % 100 == 0) {
                hero->affectByTile();
            }
            
            cout << "=======================================================" << endl;
            board->print();
            hero->printStat();
            cout << endl;
            
            if (hero->isDead()) {
                cout << "You lose!! Game Over!!" << endl;
                break;
            }
            
            if (hero->getUnitEngaged() != NULL && hero->getUnitEngaged()->isDead()) {
                hero->setUnitEngaged(NULL);
            }

        } // end of playing mode.

        // give computer player a bit of random duration of time to think.
#ifdef VISUAL_STUDIO
        Sleep(DELAY_MILLI_SECOND); // 1 sec = 1,000
#else
        usleep(DELAY_MILLI_SECOND*1000); // 1 sec = 1,000,000
#endif
        gWorldTime++;
        //cout << "gWorldTime: " << gWorldTime << endl;
    }
    cout << "Bye!!" << endl;
    
    //--------------------------------------------------------------------------
    // Edit Mode:
    //--------------------------------------------------------------------------
    if (editMode) {
        for (int i = 0; i < board->getRowSize(); i++) {
            delete [] unitItemPropLayer[i];
        }
        delete [] unitItemPropLayer;
    }
    //--------------------------------------------------------------------------

    delete board; // calling destructor of class Board.    
    
    return 0;
}
