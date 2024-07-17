#include "cellfactory.h"

Cell *CellFactory::createCell(char c, int row, int col) {
    switch (c) {
        case '|':
            return new VWall(row,col);
        case '-':
            return new HWall(row,col);

        case '+':
            return new Door(row,col);

        case '#':
            return new Passage(row,col);

        case '.':
            return new Block (row,col);

        default:
            return new Blank (row,col);
    }
}
