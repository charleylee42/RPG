#ifndef LEVELS_H
#define LEVELS_H

#define CURRENT_LEVEL_TO_LOAD 1

#define NUM_LEVELS 3

#define ROW_SIZE 20
#define COL_SIZE 40

extern char startPos[2][NUM_LEVELS];
extern char levels[NUM_LEVELS][ROW_SIZE][COL_SIZE+1];
extern char contents[NUM_LEVELS][ROW_SIZE][COL_SIZE+1];

#endif
