#include "player.h"
#include "attack.h"
#include <iostream>
#include "floor.h"
Player::~Player() {
    delete potionEater;
    delete trader;
}
void Player::move(Direction direction) {
    Cell *cell = this->getCell()->getRangeCell(direction);
    if (cell != nullptr) {
        this->addAction("moves " + dtoa(direction));
        if(cell->accept(this)){
        }else{
            this->addAction("failed");
        }
    }
}

void Player::attack(Enemy* enemy) {
    Attack attack(this, enemy);
    attack.done();
    enemy->attackedBy(this);
    if(enemy->isDead()){
        this->getGold() =this->getGold()+enemy->reward();
        enemy->onDie();
    }
}
void Player::attack(Direction direction) {
    Cell* dstCell =  this->cell->getRangeCell(direction);
    if(dstCell != nullptr && dstCell->getEnemy() != nullptr){
        dstCell->getEnemy()->accept(this);
    }else{
        this->addAction("attack " + dtoa(direction) +" failed");
    }
}

void Player::use(Item* item){
    Player* p = this;
    item->accept(p);
}
void Player::use(Direction direction){
    Cell* dstCell =  this->cell->getRangeCell(direction);
    if(dstCell != nullptr && dstCell->getItem() != nullptr){
        this->use(dstCell->getItem());
    }else{
        this->addAction("uses " + dtoa(direction) +" failed");
    }
}

void Player::visit(Block *block) {
    Cell*&  lastCell = this->getCell();
    if(lastCell != nullptr){
        lastCell ->clearPlayer();
    }
    lastCell = block;
}

void Player::visit(Door *door) {
    Cell*&  lastCell = this->getCell();
    if(lastCell != nullptr){
        lastCell ->clearPlayer();
    }
    lastCell = door;
}

void Player::visit(Passage *passage) {
    Cell*&  lastCell = this->getCell();
    if(lastCell != nullptr){
        lastCell ->clearPlayer();
    }
    lastCell = passage;
}

void Player::enterFloor(Floor& floor) {
    this->actions.clear();
    this->cell = nullptr;
    this->atkValue = this->atkValue->base();
    this->defValue = this->defValue->base();
    addAction("enter floor " + std::to_string(floor.getLevel()));
}



