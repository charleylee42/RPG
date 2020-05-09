#ifndef PROP_H
#define PROP_H

#include "main.h"

class Prop {
protected:
    char shape;
public:
    Prop();
    Prop(char shape);
    
    void print();
    
    virtual bool isClimbable();
    virtual bool giveHero();
};

class Tree : public Prop {
protected:
public:
    Tree();
    Tree(char shape);    
};

class Flower : public Prop {
protected:
public:
    Flower();
    Flower(char shape);    
    
    virtual bool isClimbable();
};

class Chest : public Prop {
protected:
public:
    Chest();
    Chest(char shape);    
};


#endif
