#include <iostream>
#include <iomanip>

using namespace std;

#include "main.h"
#include "board.h"
#include "merchant.h"

extern int _kbhit(void);

Merchant::Merchant() : Unit(DEFAULT_MERCHANT_SHAPE, -1, -1, 0, 0,
                          0, 0, 0, 0, 0, 0) {
    itemsToSell = new Inventory();
    itemsBought = new Inventory();
    
    for (int i = 0; i < DEFAULT_INVENTORY_CAPACITY; i++) {
        itemsToSell->insert(createRandomItem());
    }
}

Merchant::Merchant(char shape, int row, int col, int maxHp, int hp, int maxMp, int mp, int atk, int exp, int gold)
: Unit(shape, row, col, maxHp, hp, maxMp, mp, atk, exp, gold, 0) {
}

void Merchant::move(int dir) {
}

bool Merchant::useItem(int index) {
    return false;
}

bool Merchant::isMerchant() {
    return true;
}

void Merchant::interact(Unit *unit) {
    while (true) {
        char command;
        // ask the user '(b)uy', '(s)ell' , '(q)uit'..
        cout << "(b)uy, (s)ell, (q)uit : " << endl;
        while (!_kbhit()) {}
#ifdef VISUAL_STUDIO
        command = getch();
#else
        command = getchar();
#endif
        cout << endl << endl;
        
        //--------------------------------------------------------------------------
        // buy
        //--------------------------------------------------------------------------
        // show the user itemsToSell list and itemsBought list.
        if (command == 'b') {
            while (true) {
                cout << ">>>>>>>>>>>>>>> Items to Buy <<<<<<<<<<<<<<<" << endl;
                itemsToSell->resetIterator();
                
                int currentIndexItemsToSell = 0;
                while (itemsToSell->hasMore()) {
                    Item *currentItem = itemsToSell->next();
                    
                    cout << setw(3) << currentIndexItemsToSell << ": ";
                    
                    if (currentItem != NULL) {
                        currentItem->printFullSpec();
                        cout << endl;
                    }
                    else {
                        cout << "EMPTY" << endl;
                    }
                    
                    currentIndexItemsToSell++;
                }
                
                cout << ">>>>>>>>>>>>>>>> Items bought <<<<<<<<<<<<<<" << endl;
                itemsBought->resetIterator();
                
                int currentIndexItemsBought = 100;
                while (itemsBought->hasMore()) {
                    Item *currentItem = itemsBought->next();
                    
                    cout << setw(3) << currentIndexItemsBought << ": ";
                    
                    if (currentItem != NULL) {
                        currentItem->printFullSpec();
                        cout << endl;
                    }
                    else {
                        cout << "EMPTY" << endl;
                    }

                    currentIndexItemsBought++;
                }
                
                cout << "Please enter an index to buy(-1 to exit) : " << endl;
                int indexToBuy;
                cin >> indexToBuy;
                
                Item *itemToBuy = NULL;
                bool whichBackpack = true; // true == itemsToSell | false == itemsBought
                
                if (indexToBuy == -1) { // exit
                    break;
                }
                else if (indexToBuy >= 0 && indexToBuy < 100) { // itemsToSell
                    if (indexToBuy >= itemsToSell->size()) { // out of bound error
                        cout << "error: invalid index has been entered!" << endl;
                    }
                    itemToBuy = itemsToSell->getItemAt(indexToBuy);
                    whichBackpack = true;
                }
                else { // itemsBought
                    indexToBuy = indexToBuy-100;
                    
                    if (indexToBuy >= itemsBought->size()) { // out of bound error
                        cout << "error: invalid index has been entered!" << endl;
                    }
                    itemToBuy = itemsBought->getItemAt(indexToBuy);
                    whichBackpack = false;
                }
                
                if (itemToBuy != NULL) { // buy it!!!
                    if (unit->getGold() >= itemToBuy->getPrice()) { // enough gold?
                        if (unit->hasRoom()) { // has room?
                            unit->decGold(itemToBuy->getPrice());
                            unit->receiveItem(itemToBuy->clone());
                            
                            if (!whichBackpack) {
                                itemsBought->removeAt(indexToBuy);
                                delete itemToBuy;
                            }
                        }
                        else {
                            cout << "error: You don't have enough room to receive more items!" << endl;
                        }
                    }
                    else {
                        cout << "error: You don't have enough gold to buy the item!" << endl;
                    }
                }
                unit->printStat();
            }
        }
        
//        //--------------------------------------------------------------------------
//        // sell
//        //--------------------------------------------------------------------------
//        // show the user the items from user's inventory and backpack and itemsBought list.
//        else if (command == 's') {
//            while (true) {
//                cout << ">>>>>>>>>>>>>>>> Items bought <<<<<<<<<<<<<<" << endl;
//                itemsBought->resetIterator();
//                
//                while (itemsBought->hasMore()) {
//                    Item *currentItem = itemsBought->next();
//                    
//                    currentItem->printFullSpec();
//                    cout << endl;
//                }
//                
//                cout << ">>>>>>>>>>>>>>>>> Your items <<<<<<<<<<<<<<" << endl;
//                unit->showAllItemsWithIndex();
//                
//                cout << "Please enter an index to sell(-1 to exit) : " << endl;
//                int indexToSell;
//                cin >> indexToSell;
//                
//                if (indexToSell == -1) {
//                    break;
//                }
//                else {    
//                    Item *itemToSell = unit->removeItemByIndex(indexToSell);
//                    
//                    if (itemToSell == NULL) {
//                        cout << "error: invalid index has been entered!" << endl;
//                    }
//                    else {
//                        itemsBought->push(itemToSell);
//                        unit->incGold(itemToSell->getPrice());
//                    }
//                    
//                    unit->printStat();
//                }
//            }
//        }
//        else if (command == 'q') {
//            break;
//        }
//        else {
//            cout << "error: unknown command: (b)uy, (s)ell, (q)uit only!!" << endl;
//        }
        
    }
}
