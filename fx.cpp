#include <iostream>

using namespace std;

#include "fx.h"
#include "main.h"

Fx::Fx() { // default constructor
    
}

Fx::Fx(char shape) { // general constructor
    this->shape = shape;
}

void Fx::print() {
    cout << shape;
}
