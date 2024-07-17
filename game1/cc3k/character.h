#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <vector>
#include <cmath>
#include "direction.h"
#include "value.h"
class Cell;
class DamageCalc;
class AttackSkill;
class AttackResult;
class PotionEater;

class Character {
protected:
    Cell * cell = nullptr;

    int hpValue;
    //修饰模式
    Value* atkValue = nullptr;
    Value* defValue = nullptr;

    int gold = 0;
    //
    std::vector<std::string> actions;

    //
    DamageCalc* damageCalc = nullptr;

    //
    AttackSkill* attackSkill = nullptr;
public:
    Character(const unsigned int& HP,
              const unsigned int& Atk,
              const unsigned int& Def);
    //
    virtual void newRound(){actions.clear();}

    virtual bool doneAction(){return  !actions.empty();}

    virtual void addAction(std::string act){actions.push_back(act);}



    virtual Cell*& getCell(){return cell;}

    virtual AttackSkill*& getAttackSkill(){return attackSkill;}

    virtual void acceptAttackResultAsAttacker(AttackResult ar);

    virtual void acceptAttackResultAsVictim(AttackResult ar);

    bool isDead(){return hpValue == 0;}

    virtual int& getGold(){return gold;};

    // we do not have pure virtual method
    virtual DamageCalc*& getDamageCalc() {return damageCalc;}

    virtual Value*& getAtkValue() {return atkValue;}
    virtual Value*& getDefValue() {return defValue;}
    virtual int& getHpValue() {return hpValue;}

    virtual bool isMiss(){return false;}

    virtual std::string name() =0;


    virtual void printAction(std::ostream &out);

    virtual void move(Direction direction)  = 0;

    virtual ~Character();
};

#endif
