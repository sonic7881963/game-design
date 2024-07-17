#ifndef BARRIERSUIT_H
#define BARRIERSUIT_H

#include "item.h"
#include "enemyfactory.h"
class BarrierSuit : public Item{
public:
    BarrierSuit();
    char getDisplayChar() override{return 'B';};
    void accept(Player *&player) override;
    std::string name() override{return  "an BarrierSuit";}
    virtual ~BarrierSuit(){};
};

#endif



