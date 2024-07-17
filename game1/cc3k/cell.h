#ifndef CELL_H
#define CELL_H

#include <iostream>
#include <vector>
#include "player.h"
#include "direction.h"
#include "potion.h"
#include "compass.h"
#include "stair.h"

class Player;
class Gold;
class BarrierSuit;
class Enemy;
class Cell {
protected:
    int row;
    int col;
    int roomNo = 0;
    std::vector<Cell*> access_range;
    Enemy* enemy = nullptr;
    Player* player = nullptr;
    Item* item = nullptr;
    Stair* stair = nullptr;
    Gold* gold = nullptr;
public:
    Cell(int row,int col);
    virtual ~Cell(){};
    const int rowValue(){return row;}
    const int colValue(){return col;}
    int& getRoomNo(){return roomNo;}
    Enemy*& getEnemy(){return  enemy;};
    Player*& getPlayer(){return  player;};
    Item*& getItem(){return  item;};
    Stair*& getStair(){return  stair;};
    Gold*& getGolds(){return gold;};

    bool canAcceptEnemy(){
        return player == nullptr &&
                enemy == nullptr &&
                item == nullptr &&(stair== nullptr || !stair->getVisible());
    }

    bool canAcceptPlayer();

    bool isClear(){
        return player == nullptr &&
               enemy == nullptr &&
               item == nullptr &&
               stair == nullptr &&
               gold == nullptr;
    }
    void clearEnemy(){
        enemy = nullptr;
    }
    void clearPlayer(){
        player = nullptr;
    }

    bool canPutMore(){
        return player == nullptr &&
               enemy == nullptr &&
               item == nullptr &&
                gold == nullptr &&
                stair== nullptr;
    }
    // put things on init
    virtual  void put(Potion* pPotion);
    virtual  void put(BarrierSuit* item);
    virtual  void put(Gold* pGold);
    virtual  void put(Stair *pStair);
    //put things in playing
    virtual  void accept(Enemy* pEnemy){};
    virtual  bool accept(Player* pPlayer){ return false;};
    virtual  void accept(Item* pItem);



    void setRangeCell(Direction direction,Cell* cell){
        int i = static_cast<int>(direction);
        access_range[i] = cell;
    }
    Cell* getRangeCell(Direction direction){
        int i = static_cast<int>(direction);
        return access_range[i];
    }

    std::vector<Cell*>& getRangeCell(){ return access_range;}
    virtual void print(std::ostream &out)= 0;
    virtual bool isBlock(){return false;}
    void reset();
};

class Block :public  Cell{
protected:
    std::vector<Cell*> access_range;
public:
    Block(int row,int col):Cell(row,col){}
    void print(std::ostream &out) override ;
    void accept(Enemy* enemy) override;
    bool accept(Player* player)override;
    bool isBlock() override{return true;}

};

class Blank : public Cell {
public:
    Blank(int row,int col): Cell(row,col){}
    void print(std::ostream &out) override {out<< ' ';};
};

class VWall : public Cell {
public:
    VWall(int row,int col): Cell(row,col){}
    void print(std::ostream &out) override {out<< '|';};
};
class HWall : public Cell {
public:
    HWall(int row,int col): Cell(row,col){}
    void print(std::ostream &out) override {out<< '-';};
};
class Passage : public Cell {
public:
    Passage(int row,int col): Cell(row,col){}
    void print(std::ostream &out) override;
    bool accept(Player* player)override;

};
class Door : public Cell {
public:
    Door(int row,int col): Cell(row,col){}
    void print(std::ostream &out) override ;
    bool accept(Player* player)override;

};

#endif
