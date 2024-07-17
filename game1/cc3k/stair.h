#ifndef STAIR_H
#define STAIR_H

#include "item.h"
class Floor;
class Stair : public Item{
private:
    Floor* floor;
    bool isVisible = false;
public:
    Floor*& getFloor(){return floor;}
    char getDisplayChar() override{return '\\';}
    void accept(Player *& player) override;
    std::string name() override{return  "an stair";}
    bool& getVisible(){return isVisible;}
};

#endif



