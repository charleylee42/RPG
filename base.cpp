#include <iostream>

using namespace std;

#include "main.h"
#include "base.h"

Base::Base() { // default constructor
    type = DEFAULT_INVENTORY_CAPACITY;
}

Base::Base(int type) { // general constructor
    this->type = type;
}

//===================================
// Base Shapes
//===================================
Base::Base(char shape) {
    this->shape = shape;

    if (shape == BASE_DIRT_SHAPE) {
        type = BASE_DIRT;
        climbable = BASE_DIRT_CLIMBABLE;
        speed = BASE_DIRT_SPEED;
    }
    else if (shape == BASE_FLOOR_SHAPE) {
        type = BASE_FLOOR;
        climbable = BASE_FLOOR_CLIMBABLE;
        speed = BASE_FLOOR_SPEED;
    }
    else if (shape == BASE_WATER_SHAPE) {
        type = BASE_WATER;
        climbable = BASE_WATER_CLIMBABLE;
        speed = BASE_WATER_SPEED;
    }
    else if (shape == BASE_LAVA_SHAPE) {
        type = BASE_LAVA;
        climbable = BASE_LAVA_CLIMBABLE;
        speed = BASE_LAVA_SPEED;
    }
    else if (shape == BASE_SNOW_SHAPE) {
        type = BASE_SNOW;
        climbable = BASE_SNOW_CLIMBABLE;
        speed = BASE_SNOW_SPEED;
    }
    else if (shape == BASE_MUD_SHAPE) {
        type = BASE_MUD;
        climbable = BASE_MUD_CLIMBABLE;
        speed = BASE_MUD_SPEED;
    }
    else if (shape == BASE_MOUNTAIN_SHAPE) {
        type = BASE_MOUNTAIN;
        climbable = BASE_MOUNTAIN_CLIMBABLE;
        speed = BASE_MOUNTAIN_SPEED;
    }
    else if (shape == BASE_ROCK_SHAPE) {
        type = BASE_ROCK;
        climbable = BASE_ROCK_CLIMBABLE;
        speed = BASE_ROCK_SPEED;
    }

    else if (shape == BASE_WALL_01_SHAPE) {
        type = BASE_WALL;
        climbable = BASE_WALL_CLIMBABLE;
        speed = BASE_WALL_SPEED;
    }
    else if (shape == BASE_WALL_02_SHAPE) {
        type = BASE_WALL;
        climbable = BASE_WALL_CLIMBABLE;
        speed = BASE_WALL_SPEED;
    }
    else if (shape == BASE_WALL_03_SHAPE) {
        type = BASE_WALL;
        climbable = BASE_WALL_CLIMBABLE;
        speed = BASE_WALL_SPEED;
    }
    else if (shape == BASE_WALL_04_SHAPE) {
        type = BASE_WALL;
        climbable = BASE_WALL_CLIMBABLE;
        speed = BASE_WALL_SPEED;
    }
    else if (shape == BASE_WALL_05_SHAPE) {
        type = BASE_WALL;
        climbable = BASE_WALL_CLIMBABLE;
        speed = BASE_WALL_SPEED;
    }
    else if (shape == BASE_WALL_06_SHAPE) {
        type = BASE_WALL;
        climbable = BASE_WALL_CLIMBABLE;
        speed = BASE_WALL_SPEED;
    }
    else if (shape == BASE_WALL_07_SHAPE) {
        type = BASE_WALL;
        climbable = BASE_WALL_CLIMBABLE;
        speed = BASE_WALL_SPEED;
    }
    else if (shape == BASE_WALL_08_SHAPE) {
        type = BASE_WALL;
        climbable = BASE_WALL_CLIMBABLE;
        speed = BASE_WALL_SPEED;
    }
}

void Base::print() {
    cout << shape;
}

int Base::getSpeed() {
    return speed;
}

bool Base::isClimbable() {
    return climbable;
}

bool Base::isLava() {
    return shape == BASE_LAVA_SHAPE;
}

bool Base::isWater() {
    return shape == BASE_WATER_SHAPE;
}
