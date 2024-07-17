#ifndef DAMAGECACL_H
#define DAMAGECACL_H

class Character;

class DamageCalc {
public:
    virtual int damage(Character* attacker) = 0;
};

class DamageCalcBase: public DamageCalc{
private:
    Character* victim;
public:
    DamageCalcBase(Character* victim):victim(victim){};
    int damage(Character* attacker) override;
};


class DamageCalcDecorate: public DamageCalc{
protected:
    DamageCalc* source;
public:
    DamageCalcDecorate(DamageCalc* source):source(source){};
};


class DamageCalcBarrierSuite: public DamageCalcDecorate{
public:
    DamageCalcBarrierSuite(DamageCalc* source):DamageCalcDecorate(source){};
    int damage(Character* c) override;
};
#endif

