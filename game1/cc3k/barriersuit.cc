#include "barriersuit.h"
#include "enemyfactory.h"
#include "damagecalc.h"

BarrierSuit:: BarrierSuit() {
    EnemyFactory enemyFactory;
    enemy = enemyFactory.createDragon();
    enemy->getHoardItem() = this;

}

void BarrierSuit::accept(Player *& player) {
    if(getHoard()!= nullptr){
        player->addAction("uses the Barrier Suite with a Dragon failed");
        return;
    }
    player->getDamageCalc() = new DamageCalcBarrierSuite(player->getDamageCalc());
    player->addAction("uses a Barrier Suite");
    getCell()->getItem() = nullptr;
    delete this;
}



