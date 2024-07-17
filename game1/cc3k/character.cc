#include "character.h"
#include <ostream>
#include "damagecalc.h"
#include "attack.h"
// Constructor
Character::Character(const unsigned int& HP,
                      const unsigned int& Atk,
                      const unsigned int& Def): hpValue(HP), atkValue(new RealValue(Atk)), defValue(new RealValue(Def)) {
    damageCalc = new DamageCalcBase(this);
    attackSkill = new AttackSkillBase(this);
}

void Character::acceptAttackResultAsAttacker(AttackResult ar){
    this->hpValue+= ar.attacker_hp;
    this->atkValue->base()->getNum() += ar.attacker_at;
    this->defValue->base()->getNum() += ar.attacker_def;
    this->gold += ar.attacker_gold;

}
void Character::acceptAttackResultAsVictim(AttackResult ar){
    this->hpValue-= ar.victim_hp;
    if(this->hpValue <0){
        this->hpValue = 0;
    }
    this->atkValue->base()->getNum() -= ar.victim_at;
    this->defValue->base()->getNum() -= ar.victim_def;
    this->gold -= ar.victim_gold;
    if(this->gold <0){
        this->gold = 0;
    }

}

void Character::printAction(std::ostream &out){
    if(!actions.empty()){
        out << this->name() << " ";
    }else{
        return;
    }
    for(size_t i = 0; i < actions.size();i++){
        out<<actions[i];
        if(i !=  actions.size()-1){
            out << " and ";
        }
    }
    out << ". ";
}
// Destructor
Character::~Character() {
    delete atkValue;
    delete defValue;
    delete attackSkill;
}


