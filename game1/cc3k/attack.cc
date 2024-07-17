#include "attack.h"
#include "damagecalc.h"

void Attack::done() {
    if (attacker->doneAction()){
        return;
    }
    if (!attacker->isMiss()){
        AttackResult ar = attacker->getAttackSkill()->attack(victim);

        attacker->acceptAttackResultAsAttacker(ar);
        victim->acceptAttackResultAsVictim(ar);

        if(victim->isDead()){
            attacker->addAction("kills " + victim->name());
        } else{
            attacker->addAction("deals " + std::to_string(ar.victim_hp) + " damage to " +
                                victim->name() + "(" + std::to_string(victim->getHpValue()) + ")");
        }
    } else {
        attacker->addAction("missed");
    }
}

AttackResult AttackSkillBase::attack(Character* victim) {
    AttackResult ar;
    ar.victim_hp = victim->getDamageCalc()->damage(attacker);
    return ar;
}

// Goblin special skill
AttackResult AttackSkillStealGold::attack(Character* victim) {
    AttackResult ar = source->attack(victim);
    int gold = victim->getGold();
    if (gold > 1) {
        ar.victim_gold += 1;
        ar.attacker_gold += 1;
    }
    return ar;
}

// Vampire special skill
AttackResult AttackSkillStealHP::attack(Character* victim) {
    AttackResult ar = source->attack(victim);
    int hp = victim->getHpValue();
    if (hp > ar.victim_hp + 10) {
        ar.victim_hp += 10;
        ar.attacker_hp += 10;
    } else {
        ar.victim_hp = hp;
        ar.attacker_hp = hp - ar.victim_hp;
    }
    return ar;
}

// Werewolf special skill
AttackResult AttackSkillIncrAtk::attack(Character* victim) {
    AttackResult ar = source->attack(victim);
    ar.attacker_at += 10;
    return ar;
}

// Pheonix special skill
AttackResult AttackSkillIncrDef::attack(Character* victim) {
    AttackResult ar = source->attack(victim);
    ar.attacker_def += 10;
    return ar;
}

