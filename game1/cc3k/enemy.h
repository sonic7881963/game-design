#ifndef ENEMY_H
#define ENEMY_H
#include "cell.h"
#include "character.h"
#include "direction.h"
#include "player.h"
class Block;
class Door;
class HWall;
class VWall;
class Passage;
class Player;
class Blank;
class Passage;
class Compass;
class Item;
class Enemy : public Character {
private:
    Compass* compass =nullptr;
    Item* hoardItem = nullptr;
protected:
    Enemy(const unsigned int &HP,
          const unsigned int &Atk,
          const unsigned int &Def) : Character(HP, Atk, Def) {}

public:
    Item*& getHoardItem(){return hoardItem;}
    Compass*& getCompass(){return compass;}
    virtual char getDisplayChar() = 0;
    virtual void visit(Block *block);
    bool isMiss() override;
    virtual void visit(Door *door) {};
    virtual void visit(HWall *wall) {};
    virtual void visit(VWall *wall) {};
    virtual void visit(Blank *blank) {};
    virtual void visit(Passage *blank) {};
    void move(Direction direction) override;
    void accept(Player* player);
    virtual void attack(Player* player);
    virtual int reward(){return  1;}
    virtual void onDie();

    virtual void attackedBy(Player *pPlayer){};
};

// different Enemy class
class Vampire : public Enemy {
public: Vampire (
          const unsigned int& HP, 
          const unsigned int& Atk, 
          const unsigned int& Def): Enemy(HP, Atk, Def){};
    char getDisplayChar() override {return 'V';}
    std::string name() override{ return "V";}
};

class Werewolf : public Enemy {
public:   Werewolf(
         const unsigned int& HP, 
         const unsigned int& Atk, 
         const unsigned int& Def): Enemy(HP, Atk, Def){};
    char getDisplayChar() override {return 'W';}
    std::string name() override{ return "W";}
};

class Troll : public Enemy {
public:   Troll(
        const unsigned int& HP, 
        const unsigned int& Atk, 
        const unsigned int& Def): Enemy(HP, Atk, Def){};
    char getDisplayChar() override {return 'T';}
    std::string name() override{ return "T";}
};

class Goblin : public Enemy {
public:    Goblin(
        const unsigned int& HP, 
        const unsigned int& Atk, 
        const unsigned int& Def): Enemy(HP, Atk, Def){};
    char getDisplayChar() override {return 'N';}
    std::string name() override{ return "N";}
};

class Merchant : public Enemy {
private:
    std::vector<Merchant*> merchants;
public:
    Merchant(
            const unsigned int &HP,
            const unsigned int &Atk,
            const unsigned int &Def) : Enemy(HP, Atk, Def) {
    };
    int reward() override {return  0;}
    char getDisplayChar() override { return 'M'; }
     void attack(Player* player) override;
    std::string name() override { return "M"; }
    void attackedBy(Player *player) override;
    void  onDie()override;
};

class Dragon : public Enemy {
public:    Dragon(
        const unsigned int& HP, 
        const unsigned int& Atk, 
        const unsigned int& Def): Enemy(HP, Atk, Def){};
    char getDisplayChar() override {return 'D';}
    void move(Direction direction) override;
    std::string name() override{ return "D";}
    int reward() override {return  0;}
    void attack(Player* player) override;
};

class Phoenix : public Enemy {
public: Phoenix(
        const unsigned int& HP, 
        const unsigned int& Atk, 
        const unsigned int& Def): Enemy(HP, Atk, Def){};
    char getDisplayChar() override {return 'X';}
    std::string name() override{ return "X";}
};

#endif
