#ifndef INVENTORY_H
#define INVENTORY_H

#include "main.h"
#include "item.h"
#include "unit.h"

class Inventory {
protected:
    int capacity;
    int numItems;
    Item **slots;
    
    // member variables for Iterator
    int currentIterIndex;
    
public:
    Inventory();
    Inventory(int capacity);
    
    bool insert(Item *item);
    Item *removeAt(int indexToRemove);
    bool insertAt(int indexToInsert, Item *item);
    Item *getItemAt(int indexToReturn);
    bool useItemAt(int indexToUse, Unit *unit);
    
    void print();
    
    bool isFull();
    int size();
    
    // Iterator
    bool hasMore();
    Item *next();
    
    void resetIterator();
};

#endif
