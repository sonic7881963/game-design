#ifndef ENEMYFACTORY_H
#define ENEMYFACTORY_H

#include <vector>
#include "enemy.h"
class Vampire;
class Werewolf;
class Troll;
class Goblin;
class Merchant;
class Dragon;
class Phoenix;

class EnemyFactory {
public:
    std::vector<Enemy*> create20();

    Enemy *create(char c);

    Vampire *createVampire();

    Werewolf *createWerewolf();

    Troll *createTroll();

    Goblin *createGoblin();

    Merchant *createMerchant();

    Dragon *createDragon();

    Phoenix *createPhoenix();
};

#endif
