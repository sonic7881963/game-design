#ifndef FLOOR_H
#define FLOOR_H
#include <string>
#include <vector>
#include "cell.h"
class Game;
class Room {
private:
    std::vector<Cell*> blockCells;
public:
    std::vector<Cell*>& getAllBlocks(){return blockCells;};
    std::vector<Cell*> getFreeBlocks();
    virtual ~Room(){blockCells.clear();}
};

class Floor {
private:
    const int width = 79;
    const int height = 25;
    std::vector<std::vector<Cell*>> cells;
    std::vector<Cell*> blockCells;
    std::vector<Room> rooms;
    int level;
    Player* player = nullptr;
    Game* game = nullptr;
    int luckyLevel = 0;
public:
    Floor(int floorNo);
    void nextFloor();
    Game*& getGame(){return game;}
    int& getLuckyLevel(){ return luckyLevel;}
    int& getLevel(){return  level;};
    Player*& getPlayer(){return player;};
    std::vector<Room>& getRooms(){return  rooms;}
    int getWidth(){return width;};
    int getHeight(){return height;};
    std::vector<std::vector<Cell*>>& getCells(){return cells;}
    std::vector<Cell*>& getblockCells(){return blockCells;}
    void resetAllCellState();
    void removeAllCell();
    void spawn();
    void enemyAutoAct();
    void newRound();
    void createRangeCell();
    void createRooms();
    virtual ~Floor();
};

std::istream &operator>>(std::istream &in, Floor &floor);

std::ostream &operator<<(std::ostream &out, Floor &floor);

#endif
