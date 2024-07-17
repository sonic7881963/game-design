#ifndef COMPASS_H
#define COMPASS_H

#include "item.h"
class Stair;

class Compass : public Item{
private:
    Stair* stair = nullptr;
public:
    Stair* & getStair(){return  stair;};
    char getDisplayChar() override{return 'C';};
    void accept(Player *& player) override;
    std::string name() override{return  "an compass";};

};


#endif


