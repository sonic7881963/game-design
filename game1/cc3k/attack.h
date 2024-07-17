#ifndef ATTACK_H
#define ATTACK_H
#include "character.h"
#include <cmath>

class Attack {
private:
    Character* attacker;
    Character* victim;
public:
    Attack(Character* source,Character* dest): attacker(source), victim(dest){}
    void done();
};


class AttackResult{
public:
    int victim_hp = 0;
    int victim_at= 0;
    int victim_def= 0;
    int victim_gold= 0;

    int attacker_hp= 0;
    int attacker_at= 0;
    int attacker_def= 0;
    int attacker_gold= 0;
};


class AttackSkill{
protected:
    Character* attacker= nullptr;
public:
    explicit AttackSkill(Character* attacker):attacker(attacker){}
    virtual AttackResult attack(Character* victim) =0;
    virtual ~AttackSkill(){}
};


class AttackSkillBase:public AttackSkill{
public:
    explicit AttackSkillBase( Character* attacker):AttackSkill(attacker){}
    AttackResult attack(Character* victim) override;
};

class AttackSkillDecorator:public AttackSkill{
protected:
    AttackSkill *source = nullptr;
public:
    AttackSkillDecorator(Character* attacker,AttackSkill *source):AttackSkill(attacker),source(source){}
};


class AttackSkillStealGold:public AttackSkillDecorator{
public:
    AttackSkillStealGold(Character* attacker,AttackSkill *source):AttackSkillDecorator(attacker,source){}
    AttackResult attack(Character* victim) override;
};

class AttackSkillStealHP:public AttackSkillDecorator{
public:
    AttackSkillStealHP(Character* attacker,AttackSkill *source):AttackSkillDecorator(attacker,source){}
    AttackResult attack(Character* victim) override;
};

class AttackSkillIncrAtk:public AttackSkillDecorator{
public:
    AttackSkillIncrAtk(Character* attacker,AttackSkill *source):AttackSkillDecorator(attacker,source){}
    AttackResult attack(Character* victim) override;
};

class AttackSkillIncrDef:public AttackSkillDecorator{
public:
    AttackSkillIncrDef(Character* attacker,AttackSkill *source):AttackSkillDecorator(attacker,source){}
    AttackResult attack(Character* victim) override;
};

#endif

