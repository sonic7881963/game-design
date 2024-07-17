#include "damagecalc.h"
#include "character.h"
#include <cmath>

int DamageCalcBase::damage(Character *attacker) {
    return ceil((100.0 / (100.0 + victim->getDefValue()->value())) * attacker->getAtkValue()->value());
}

int DamageCalcBarrierSuite::damage(Character *c) {
    return source->damage(c)/2;
}
