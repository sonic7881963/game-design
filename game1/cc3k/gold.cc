#include "gold.h"
#include "enemy.h"
#include "enemyfactory.h"

void Gold::accept(Player *& player) {
    if(this->hasHoard()){
        return;
    }
   int &gold = player->getGold();
    gold = gold + this->getNum();
    player->addAction("uses a Gold");
    getCell()->getGolds() = nullptr;
    delete this;
}

GoldDragonHoard::GoldDragonHoard():Gold(6) {
    EnemyFactory enemyFactory;
    enemy = enemyFactory.createDragon();
    enemy->getHoardItem() = this;
}

GoldFactory:: GoldFactory(){
for(int i=0 ;i < 100; i++){
    pts.push_back(GoldType::NORMAL);
    pts.push_back(GoldType::NORMAL);
    pts.push_back(GoldType::NORMAL);
    pts.push_back(GoldType::NORMAL);
    pts.push_back(GoldType::NORMAL);
    pts.push_back(GoldType::SMALLHOARD);
    pts.push_back(GoldType::SMALLHOARD);
    pts.push_back(GoldType::DRAGONHOARD);
}
}
std::vector<Gold*> GoldFactory::create10() {
    std::vector<Gold*> golds;
    for (int i = 0; i < 10; i++) {
        int index = Shuffer::getLuckNum(pts.size());
        GoldType pt =pts[index];
        golds.push_back(create(pt));
    }
    return golds;
};

Gold* GoldFactory::create(GoldType pt){
    switch (pt) {
        case GoldType::NORMAL:
            return new GoldNormal();
        case GoldType::SMALLHOARD:
            return new GoldSmallHoard();
        case GoldType::DRAGONHOARD:
            return new GoldDragonHoard();
        default:
            return new GoldMerchantHoard();
    }
}




