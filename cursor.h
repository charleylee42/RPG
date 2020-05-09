#ifndef CURSOR_H
#define CURSOR_H

class Board;

class Cursor {
protected:
    char shape;
    int row;
    int col;
    
    Board *board;

public:
    Cursor();    
    Cursor(char shape, int row, int col);
    
    void print();
    
    int getRow();
    void setRow(int row);
    int getCol();
    typedef int(^block)(bool);
    void setCol(int col);
    
    void setBoard(Board *board);
    
    virtual void move(int dir);
};

#endif
