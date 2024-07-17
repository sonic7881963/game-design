#ifndef POTION_H
#define POTION_H

#include "item.h"
#include "value.h"

#include <vector>
enum PotionType {RH, BA, BD, PH, WA, WD};
class Player;

class PotionValue{
public:
    PotionValue(int hp,int atk,int def):hp(hp),atk(atk),def(def){}
    int hp =0;
    int atk =0;
    int def =0;
};

class Potion : public Item{
protected:
    PotionValue pv;
public:
    Potion(PotionValue pv):pv(pv){}
    PotionValue& getValue(){return pv;};
    char getDisplayChar() override{return 'P';};
    void accept(Player *& player) override;
    std::string name() override{return  "an unknown Potion";};
};

class PotionRH : public Potion {
public:
    PotionRH():Potion({10,0,0}){}
    void accept(Player *& player) override;

};
class PotionBA : public Potion {
public:
    PotionBA():Potion({0,5,0}){}
    void accept(Player *& player) override;

};
class PotionBD : public Potion {
public:
    PotionBD():Potion({0,0,5}){}
    void accept(Player *& player) override;

};

class PotionPH : public Potion {
public:
    PotionPH():Potion({0,-10,0}){}
    void accept(Player *& player) override;

};

class PotionWA : public Potion {
public:
    PotionWA():Potion({0,-5,0}){}
    void accept(Player *& player) override;

};
class PotionWD : public Potion {
public:
    PotionWD():Potion({0,0,-5}){}
    void accept(Player *& player) override;

};

class PotionEater {
protected:
    Player* eater= nullptr;
public:
    PotionEater( Player* eater):eater(eater){}
    virtual void eat(Potion* potion)=0;
    virtual ~PotionEater(){}
};

class PotionEaterNormal:public PotionEater{
public:
    PotionEaterNormal( Player* eater):PotionEater(eater){}
    void eat(Potion* potion)override;
};

class PotionEaterSpecial:public PotionEater{
public:
    PotionEaterSpecial( Player* eater):PotionEater(eater){}
    void eat(Potion* potion)override;
};

class PotionFactory{
private:
    std::vector<PotionType> pts;
public:
    PotionFactory();
    std::vector<Potion*> create10() ;
    Potion* create(PotionType pt);
};
#endif


