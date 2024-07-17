#ifndef CELLFACTORY_H
#define CELLFACTORY_H

#include "cell.h"
class CellFactory {
public:
    static Cell* createCell(char c,int row,int col);
};


#endif 
