#ifndef PLAYER_H
#define PLAYER_H


#include <vector>
#include <string>

#include <cmath>
#include "cell.h"
#include "enemy.h"
#include "direction.h"
#include "character.h"
#include "stair.h"
#include "potion.h"
#include "trader.h"

class Block;
class Door;
class Passage;
class Enemy;
class Floor;
class Player : public Character {
private:
    PotionEater* potionEater = nullptr;
    Trader* trader = nullptr;
    bool merchantKiller = false;
    bool roundTreasure = false;
public:
    Player(const unsigned int &HP,
           const unsigned int &Atk,
           const unsigned int &Def) : Character(HP, Atk, Def){
        addAction("character has spawned");
    };

    virtual ~Player();
    bool& getMerchantKiller(){return merchantKiller;}
    bool& getRoundTreasure(){return roundTreasure;}

    void move(Direction direction) override;
    PotionEater*& getPotionEater(){return potionEater;}
    Trader*& getTrader(){return trader;}

    void visit(Block *block);
    void visit(Door *door);
    void visit(Passage *passage);
    void attack(Enemy* enemy);
    void attack(Direction direction);

    void use(Item* enemy);
    void use(Direction direction);

    void enterFloor(Floor& floor);
};
//
//// Player races classes
class Human : public Player {
public:
    Human( const unsigned int& HP,
          const unsigned int& Atk,
          const unsigned int& Def): Player(HP,Atk,Def){
        getPotionEater() = new PotionEaterNormal(this);
        getTrader() = new TraderNormal(this);
    };
    std::string name() override {return "Human";};
};

class Dwarf : public Player {
public:
    Dwarf(const unsigned int& HP,
          const unsigned int& Atk,
          const unsigned int& Def): Player(HP,Atk,Def){
        getPotionEater() = new PotionEaterNormal(this);
        getTrader() = new TraderWorthDouble(this);

    };
    std::string name() override {return "Dwarf";};
};

class Elves : public Player {
public:
    Elves(
          const unsigned int& HP,
          const unsigned int& Atk,
          const unsigned int& Def): Player(HP,Atk,Def){
        getPotionEater() = new PotionEaterSpecial(this);
        getTrader() = new TraderNormal(this);

    };
    std::string name() override {return "Elves";};
};

class Orc : public Player {
public:
    Orc(
        const unsigned int& HP,
        const unsigned int& Atk,
        const unsigned int& Def): Player(HP,Atk,Def){
        getPotionEater() = new PotionEaterNormal(this);
        getTrader() = new TraderWorthHalf(this);

    };
    std::string name() override {return "Orc";};
};
#endif

