#include <iostream>

using namespace std;

#include "prop.h"

Prop::Prop() { // default constructor
    shape = DEFAULT_PROP_SHAPE;
}

Prop::Prop(char shape) { // general constructor
    this->shape = shape;
}

void Prop::print() {
    cout << shape;
}

bool Prop::isClimbable() {
    // N/A
    return false;
}

bool Prop::giveHero() {
    //N/A
    return false;
}

Tree::Tree() : Prop(DEFAULT_TREE_SHAPE) { // default constructor
}

Tree::Tree(char shape) : Prop(shape) { // general constructor
}

Flower::Flower() : Prop(DEFAULT_FLOWER_SHAPE) { // default constructor
}

Flower::Flower(char shape) : Prop(shape) { // general constructor
}

bool Flower::isClimbable() {
    return true;
}

Chest::Chest() : Prop(DEFAULT_CHEST_SHAPE) { // default constructor
}

Chest::Chest(char shape) : Prop(shape) { // general constructor
}

//bool Chest::giveHero() {
//    if (unlocked) {
//        return true;
//    }
//}
