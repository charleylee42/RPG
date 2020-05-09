#include <iostream>

using namespace std;

#include "main.h"
#include "board.h"
#include "cursor.h"

Cursor::Cursor() {
    shape = DEFAULT_CURSOR_SHAPE;
    row = -1;
    col = -1;
}

Cursor::Cursor(char shape, int row, int col) {
    this->shape = shape;
    this->row = row;
    this->col = col;
}

void Cursor::print() {
    cout << shape;
}

int Cursor::getRow() {
    return row;
}

void Cursor::setRow(int row) {
    this->row = row;
}

int Cursor::getCol() {
    return col;
}

void Cursor::setCol(int col) {
    this->col = col;
}

void Cursor::setBoard(Board *board) {
    this->board = board;
}

void Cursor::move(int dir) {
    if (dir == DIR_NORTH) {
        if (board->validate(row-1, col)) {
            board->setCursor(row, col, NULL);
            board->setCursor(row-1, col, this);
        }
    }
    else if (dir == DIR_EAST) {
        if (board->validate(row, col+1)) {
            board->setCursor(row, col, NULL);
            board->setCursor(row, col+1, this);
        }
    }
    else if (dir == DIR_SOUTH) {
        if (board->validate(row+1, col)) {
            board->setCursor(row, col, NULL);
            board->setCursor(row+1, col, this);
        }
    }
    else if (dir == DIR_WEST) {
        if (board->validate(row, col-1)) {
            board->setCursor(row, col, NULL);
            board->setCursor(row, col-1, this);
        }
    }
}
