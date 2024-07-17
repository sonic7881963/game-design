#include "enemyfactory.h"
#include <algorithm>
#include <random>
#include <chrono>
#include "enemy.h"
#include "attack.h"

std::vector<Enemy*> EnemyFactory::create20() {
    std::vector<char> que ;

    que.push_back('W');
    que.push_back('W');
    que.push_back('W');
    que.push_back('W');

    que.push_back('V');
    que.push_back('V');
    que.push_back('V');

    que.push_back('N');
    que.push_back('N');
    que.push_back('N');
    que.push_back('N');
    que.push_back('N');

    que.push_back('T');
    que.push_back('T');

    que.push_back('X');
    que.push_back('X');

    que.push_back('M');
    que.push_back('M');
    std::vector<Enemy*> enemys;
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng{seed};

    for(int i =0;  i< 20; i++)
    {
        std::shuffle( que.begin(), que.end(), rng );
        enemys.push_back(create(que[0]));
    }
    return  enemys;
}

Enemy* EnemyFactory::create(char c){
    switch (c) {
        case 'V':
            return this->createVampire();
        case 'W':
            return this->createWerewolf();
        case 'N':
            return this->createGoblin();
        case 'M':
            return this->createMerchant();
        case 'D':
            return this->createDragon();
        case 'X':
            return this->createPhoenix();
        case 'T':
            return this->createTroll();
        default:
            return this->createTroll();
    }
}

Vampire* EnemyFactory::createVampire() {
    Vampire* v=  new Vampire (50, 25, 25);
    v->getAttackSkill() = new AttackSkillStealHP(v,v->getAttackSkill());
    return v;
}

Werewolf* EnemyFactory::createWerewolf() {
    Werewolf* w = new Werewolf(120, 30, 5);
    w->getAttackSkill() = new AttackSkillIncrAtk(w,w->getAttackSkill());

    return  w;
}

Troll* EnemyFactory::createTroll() {
    return  new Troll (120, 25, 15);
}

Goblin* EnemyFactory::createGoblin() {
    Goblin* g = new Goblin (70, 5, 10);
    g->getAttackSkill() = new AttackSkillStealGold(g,g->getAttackSkill());
    return  g;
}

Merchant* EnemyFactory::createMerchant() {
    return new Merchant (30, 70, 5);
}

Dragon* EnemyFactory::createDragon() {
    return new Dragon (150, 20, 20);
}

Phoenix* EnemyFactory::createPhoenix() {
    Phoenix* p = new Phoenix ( 50, 35, 20);
    p->getAttackSkill() = new AttackSkillIncrDef(p,p->getAttackSkill());

    return p;
}
