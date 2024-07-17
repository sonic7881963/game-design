#ifndef GOLD_H
#define GOLD_H
#include <vector>
#include "item.h"
#include "enemyfactory.h"
#include "shuffer.h"

class Enemy;
enum GoldType {NORMAL, SMALLHOARD, MERCHANETHOARD, DRAGONHOARD};
class Gold : public Item{
int num = 0;
public:
    Gold(int num):num(num){}
    int getNum(){return num;}
    virtual bool hasHoard(){return  false;}
    char getDisplayChar() override{return 'G';};
    void accept(Player*&  player) override;
    std::string name() override{return  "an gold";};

};

class GoldNormal:public Gold{
public:
    GoldNormal():Gold(1){}
};

class GoldSmallHoard:public Gold{
public:
    GoldSmallHoard():Gold(2){}
};

class GoldMerchantHoard:public Gold{
public:
    GoldMerchantHoard():Gold(4){}
};

class GoldDragonHoard:public Gold{
public:
    GoldDragonHoard();
};

class GoldFactory{
private:
    std::vector<GoldType> pts;
public:
    GoldFactory();
    std::vector<Gold*> create10() ;

    Gold* create(GoldType pt);
};
#endif



