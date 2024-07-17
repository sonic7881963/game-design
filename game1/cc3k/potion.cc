
#include "value.h"
#include "player.h"
#include <vector>
#include "potion.h"
#include "shuffer.h"

void Potion::accept(Player*&  player) {
    player->getPotionEater()->eat(this);
    getCell()->getItem() = nullptr;
    delete this;
}

void PotionRH::accept(Player*&  player) {
    player->addAction("uses a potion(RH)");
    Potion::accept(player);
}

void PotionBA::accept(Player*&  player) {

    player->addAction("uses a potion(BA)");
    Potion::accept(player);
}

void PotionBD::accept(Player*&  player) {
    player->addAction("uses a potion(BD)");
    Potion::accept(player);
}

void PotionPH::accept(Player*&  player) {
    player->addAction("uses a potion(PH)");
    Potion::accept(player);
}

void PotionWA::accept(Player*&  player) {
    player->addAction("uses a potion(WA)");
    Potion::accept(player);
}

void PotionWD::accept(Player*&  player) {
    player->addAction("uses a potion(WD)");
    Potion::accept(player);
}


PotionFactory::PotionFactory(){
    pts.push_back(PotionType::PH);
    pts.push_back(PotionType::BA);
    pts.push_back(PotionType::BD);

    pts.push_back(PotionType::RH);
    pts.push_back(PotionType::WA);
    pts.push_back(PotionType::WD);

}
std::vector<Potion*>  PotionFactory::create10() {
    std::vector<Potion*> potions;
    for (int i = 0; i < 10; i++) {
        int index = Shuffer::getLuckNum(pts.size());
        PotionType pt =pts[index];
        potions.push_back(create(pt));
    }
    return potions;
};
Potion*  PotionFactory::create(PotionType pt) {
    switch (pt) {
        case PotionType::RH:
            return new PotionRH();
        case PotionType::BA:
            return new PotionBA();
        case PotionType::BD:
            return new PotionBD();
        case PotionType::PH:
            return new PotionPH();
        case PotionType::WA:
            return new PotionWA();
        default:
            return new PotionWD();
    }
}

void PotionEaterNormal::eat(Potion* potion) {
    eater->getHpValue() += potion->getValue().hp;

    if (potion->getValue().atk != 0) {
        Value *&atkValue = eater->getAtkValue();
        atkValue = new TmpValue(atkValue, potion->getValue().atk);
    }

    if (potion->getValue().def != 0) {
        Value *&defValue = eater->getDefValue();
        defValue = new TmpValue(defValue, potion->getValue().def);
    }
}

int turnPositive(int i){
    return i<0 ?i*-1:i;
}


void PotionEaterSpecial::eat(Potion* potion){
    eater->getHpValue() += turnPositive(potion->getValue().hp);

    if (potion->getValue().atk != 0) {
        Value *&atkValue = eater->getAtkValue();
        atkValue = new TmpValue(atkValue, turnPositive(potion->getValue().atk));
    }

    if (potion->getValue().def != 0) {
        Value *&defValue = eater->getDefValue();
        defValue = new TmpValue(defValue, turnPositive(potion->getValue().def));
    }
}


