#include <iostream>

using namespace std;

#include "inventory.h"

Inventory::Inventory() {
    capacity = DEFAULT_INVENTORY_CAPACITY;
    numItems = 0;
    slots = new Item *[capacity];

    for (int i = 0; i < capacity; i++) {
        slots[i] = NULL;
    }
    
    currentIterIndex = 0;
}

Inventory::Inventory(int capacity) {
    this->capacity = capacity;
    numItems = 0;
    slots = new Item *[capacity];

    for (int i = 0; i < capacity; i++) {
        slots[i] = NULL;
    }
    
    currentIterIndex = 0;
}

bool Inventory::insert(Item *item) {
    if (numItems >= capacity) {
        return false;
    }
    
    for (int i = 0; i < capacity; i++) {
        if (slots[i] == NULL) {
            slots[i] = item;
            numItems++;
            return true;
        }
    }
    
    return false;
}

Item *Inventory::removeAt(int indexToRemove) {
    if (indexToRemove < 0 || indexToRemove >= capacity) {
        cout << "error:Inventory::removeAt(): invalid index to remove an item!" << endl;
        return NULL;
    }
    
    Item *itemToReturn = slots[indexToRemove];
    
    if (slots[indexToRemove] != NULL) {
        slots[indexToRemove] = NULL;
        numItems--;
    }
    
    return itemToReturn;
}

bool Inventory::insertAt(int indexToInsert, Item *item) {
    if (indexToInsert < 0 || indexToInsert >= capacity) {
        cout << "error:Inventory::insertAt(): invalid index to insert an item!" << endl;
        return false;
    }
    
    if (slots[indexToInsert] != NULL) {
        return false;
    }
    
    slots[indexToInsert] = item;
    numItems++;
    
    return true;
}

Item *Inventory::getItemAt(int indexToReturn) {
    if (indexToReturn < 0 || indexToReturn >= capacity) {
        cout << "error:Inventory::getItemAt(): invalid index to retrieve an item!" << endl;
        return NULL;
    }

    return slots[indexToReturn];
}

bool Inventory::useItemAt(int indexToUse, Unit *unit) {
    if (indexToUse < 0 || indexToUse >= capacity) {
        cout << "error:Inventory::useItemAt(): invalid index to access an item!" << endl;
        return NULL;
    }
    
    if (slots[indexToUse] == NULL) {
        cout << "error:Inventory::useItemAt(): no item at the given index!" << endl;
        return false;
    }
    
    bool result = slots[indexToUse]->use(unit);
    
    if (slots[indexToUse]->getMoved()) { // weapon/armorì˜ ê²½ìš°..
        slots[indexToUse] = NULL;
        numItems--;
    }
    else if (slots[indexToUse]->getDestroy()) { // potion/breadì˜ ê²½ìš°..
        delete slots[indexToUse];
        slots[indexToUse] = NULL;
        numItems--;
    }
    
    return result;
}

void Inventory::print() {
    cout << "[";
    for (int i = 0; i < capacity; i++) {
        if (slots[i] != NULL) {
            slots[i]->print();
        }
        else {
            cout << " ";
        }
        
        if (i < capacity-1) {
            cout << "|";
        }
    }
    cout << "]" << endl;
    
    cout << " ";
    for (int i = 0; i < capacity; i++) {
        cout << i+1 << " ";
    }
    cout << endl;
}

bool Inventory::isFull() {
    return numItems >= capacity;
}

int Inventory::size() {
    return numItems;
}

//------------------------------------------------------------------------------
// Iterator
//------------------------------------------------------------------------------
bool Inventory::hasMore() {
    return currentIterIndex < capacity;
}

Item *Inventory::next() {
    return slots[currentIterIndex++];
}

void Inventory::resetIterator() {
    currentIterIndex = 0;
}
