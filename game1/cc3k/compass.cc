#include "compass.h"
#include "player.h"
void Compass::accept(Player *& player) {
    this->getStair()->getVisible() = true;
    player->addAction("uses a Compass and the stair is seen");
    getCell()->getItem() = nullptr;
    delete this;
}



