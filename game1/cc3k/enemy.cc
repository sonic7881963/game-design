#include "enemy.h"
#include "character.h"
#include "cell.h"
#include "attack.h"
#include <algorithm>
#include "gold.h"

void Enemy::visit(Block* block){
    Cell*&  lastCell = this->getCell();
    if(lastCell != nullptr){
        lastCell ->clearEnemy();
    }
    this->cell= block;
}
void Enemy::onDie(){
    this->getCell()->getEnemy() = nullptr;
    if(getCompass() != nullptr){
        this->getCell()->accept(getCompass());
    }
    if(getHoardItem() != nullptr){
        getHoardItem()->getHoard() = nullptr;
    }
    delete this;
}
bool Enemy::isMiss() {
    int luckNum = Shuffer::getLuckNum(100);
    return luckNum% 2 == 0;
}

void Enemy::move(Direction direction) {
    Cell *cell = this->getCell()->getRangeCell(direction);
    if (cell != nullptr) {
        cell->accept(this);
    }
}
void Enemy::accept(Player* player) {
    player->attack(this);
}
void Enemy::attack(Player* player) {
    Attack attack(this, player);
    attack.done();
}

void Merchant::attackedBy(Player *player) {
    player->getMerchantKiller() = true;
}
void Merchant::onDie() {
    GoldFactory goldFactory;
    Gold *gold = goldFactory.create(GoldType::MERCHANETHOARD);
    this->getCell()->put(gold);
    Enemy::onDie();
}

void Merchant::attack(Player* player) {
    if(player->getMerchantKiller()) {
        Attack attack(this, player);
        attack.done();
    }
}

void Dragon::attack(Player* player) {
    if(player->getRoundTreasure()) {
        Attack attack(this, player);
        attack.done();
    }
}

void Dragon::move(Direction direction) {

}
