#ifndef ITEM_H
#define ITEM_H
#include <string>
class Player;
class Cell;
class Enemy;

class Item{
protected:
    Enemy* enemy= nullptr;
    Cell* cell= nullptr;
public:
    virtual char getDisplayChar() = 0;
    virtual Cell*& getCell() {return  cell;};
    virtual void accept(Player*&  player) = 0;
    virtual std::string name() = 0;
    virtual Enemy*& getHoard(){ return enemy;}
    virtual~Item(){}
};
#endif
