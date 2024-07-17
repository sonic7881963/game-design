
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <iomanip>

using std::ostringstream;
using std::endl;
using std::ifstream;
#include "floor.h"
#include "cellfactory.h"
#include "gold.h"

#include "enemyfactory.h"
#include "direction.h"
#include "player.h"
#include "potion.h"
#include "stair.h"
#include "barriersuit.h"

#include "game.h"

Floor::Floor(int floorNo): level(floorNo) {}
std::vector<Cell*> Room::getFreeBlocks() {
    std::vector<Cell *> freeBlockCells;
    for (Cell *c: blockCells) {
        if (c->isClear()) {
            freeBlockCells.push_back(c);
        }
    }
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng{seed};
    std::shuffle(freeBlockCells.begin(), freeBlockCells.end(), rng);
    return freeBlockCells;
}

void Floor::spawn() {
    int playerRoomNo = Shuffer::getLuckNum(rooms.size());
    int stairRoomNo = Shuffer::getLuckNum(rooms.size());
    while(playerRoomNo == stairRoomNo){
        stairRoomNo = Shuffer::getLuckNum(rooms.size());
    }

    //player
    std::vector<Cell*> freeBlocks = rooms[stairRoomNo].getFreeBlocks();
    freeBlocks[0]->accept(player);

    // stair
    freeBlocks = rooms[playerRoomNo].getFreeBlocks();
    Stair* stair = new Stair();
    stair->getFloor() = this;
    freeBlocks[0]->put(stair);

    //potion
    PotionFactory potionFactory;
    std::vector<Potion*> potions = potionFactory.create10();
    for(int i = 0; i < 10; i++){
        int potionRoomNo = Shuffer::getLuckNum(rooms.size());
        freeBlocks = rooms[potionRoomNo].getFreeBlocks();
        freeBlocks[0]->put(potions[i]);
    }
    //gold
    GoldFactory goldFactory;
    std::vector<Gold*> golds = goldFactory.create10();
    for(int i = 0; i < 10; i++){
        int goldRoomNo = Shuffer::getLuckNum(rooms.size());
        freeBlocks = rooms[goldRoomNo].getFreeBlocks();
        freeBlocks[0]->put(golds[i]);
    }
    //Enemy
    EnemyFactory enemyFactory;
    std::vector<Enemy*> enemys = enemyFactory.create20();
    for(int i = 0; i < 20; i++){
        int enemyRoomNo = Shuffer::getLuckNum(rooms.size());
        freeBlocks = rooms[enemyRoomNo].getFreeBlocks();
        freeBlocks[0]->accept(enemys[i]);
    }
    int luckyEnemyNo = Shuffer::getLuckNum(20);
    Compass*& compass =enemys[luckyEnemyNo]->getCompass();
    compass = new Compass();
    compass->getStair() = stair;

    if(level == luckyLevel){
        int enemyRoomNo = Shuffer::getLuckNum(rooms.size());
        freeBlocks = rooms[enemyRoomNo].getFreeBlocks();
        freeBlocks[0]->put(new BarrierSuit());
    }
}

void Floor::enemyAutoAct() {
    std::vector<Enemy *> enemys;
    for (int i = 0; i < getHeight(); i++) {
        for (int j = 0; j < getWidth(); j++) {
            Cell *cell = cells[i][j];
            Enemy *enemy = cell->getEnemy();
            if (enemy != nullptr) {
                enemys.push_back(enemy);
            }
        }
    }
    for (Enemy *enemy: enemys) {
        int luckDir = Shuffer::getLuckNum(8);
        enemy->move(itod(luckDir));
    }

    //
    Cell *cell = player->getCell();
    std::vector<Cell *> &rangeCells = cell->getRangeCell();
    for (Cell *rangeCell: rangeCells) {
        if (rangeCell == nullptr) {
            continue;
        }
        if (rangeCell->getEnemy() != nullptr) {
            rangeCell->getEnemy()->attack(player);
        }
        if (rangeCell->getItem() != nullptr &&
            rangeCell->getItem()->getHoard() != nullptr) {
            player->getRoundTreasure() = true;
            rangeCell->getItem()->getHoard()->attack(player);
            player->getRoundTreasure() = false;
        }
        if (rangeCell->getGolds() != nullptr &&
            rangeCell->getGolds()->getHoard() != nullptr) {
            player->getRoundTreasure() = true;
            rangeCell->getGolds()->getHoard()->attack(player);
            player->getRoundTreasure() = false;
        }
    }
}


void Floor::newRound() {
    this->player->newRound();
    for(int i =0;i < getHeight();i ++){
        for(int j =0;j < getWidth();j ++){
            Cell* cell = cells[i][j];
            Enemy* enemy = cell->getEnemy();
            if(enemy!= nullptr){
                enemy->newRound();
            }
        }
    }
}

std::istream &operator>>(std::istream &in, Floor &floor) {
    floor.removeAllCell();
    std::vector<std::vector<Cell *>> &cells = floor.getCells();
    std::vector<Cell *> &blockCells = floor.getblockCells();
    std::string line;
    for (int i = 0; i < floor.getHeight(); i++) {
        std::getline(in, line);
        std::vector<Cell *> cell_line;
        for (int j = 0; j < floor.getWidth(); j++) {
            Cell *cell = CellFactory::createCell(line[j], i, j);
            cell_line.push_back(cell);
            if (cell->isBlock()) {
                blockCells.push_back(cell);
            }
        }
        cells.push_back(cell_line);
    }
    floor.createRangeCell();
    floor.createRooms();
    return in;
}

void Floor::createRangeCell(){
    for (int i = 0; i < getHeight(); i++) {
        for (int j = 0; j < getWidth(); j++) {
            cells[i][j]->getRangeCell().clear();
            cells[i][j]->getRangeCell().resize(8);
            if (i > 0 && j > 0) {
                cells[i][j]->setRangeCell(Direction::NW, cells[i - 1][j - 1]);
            }
            if (i > 0 && j < getWidth() - 1) {
                cells[i][j]->setRangeCell(Direction::NE, cells[i - 1][j + 1]);
            }
            if (i < getHeight() - 1 && j > 0) {
                cells[i][j]->setRangeCell(Direction::SW, cells[i + 1][j - 1]);
            }
            if (i < getHeight() - 1 && j < getWidth() - 1) {
                cells[i][j]->setRangeCell(Direction::SE, cells[i + 1][j + 1]);
            }
            // common direction
            if (i > 0) cells[i][j]->setRangeCell(Direction::N, cells[i - 1][j]);
            if (i < getHeight() - 1) cells[i][j]->setRangeCell(Direction::S, cells[i + 1][j]);
            if (j > 0) cells[i][j]->setRangeCell(Direction::W, cells[i][j - 1]);
            if (j < getWidth() - 1) cells[i][j]->setRangeCell(Direction::E, cells[i][j + 1]);
        }
    }
}
void Floor::createRooms() {
    //resetAllCellState
    for (Cell *c: blockCells) {
        c->getRoomNo() = 0;
    }
    rooms.clear();

    int curRoomNo = 1;
    for (Cell *c: blockCells) {
        int &roomNo = c->getRoomNo();
        if (roomNo == 0) { // if the cell is not in a room
            //create a new room
            Room room;
            roomNo = curRoomNo;
            std::vector<Cell *> &cellsInRoom = room.getAllBlocks();
            // put  the cell  into a tmp vector
            std::vector<Cell *> tmpcells;
            tmpcells.push_back(c);
            while (!tmpcells.empty()) { // if the tmp vector is not empty
                // get the first cell
                Cell *tc = tmpcells[0];
                tmpcells.erase(std::begin(tmpcells));

                // put the cell into the room
                cellsInRoom.push_back(tc);
                // put all the cell's range cell into the tmp vector
                std::vector<Cell *> &rangcells = tc->getRangeCell();
                for (Cell *rangcell: rangcells) {
                    // if the range cell is not in a room ,discard repeat put cell into the room
                    if (rangcell != nullptr && rangcell->getRoomNo() == 0 && rangcell->isBlock()) {
                        //set room number
                        int &rangcellRoomNo = rangcell->getRoomNo();
                        rangcellRoomNo = curRoomNo;
                        // put  the range cell  into the tmp vector
                        tmpcells.push_back(rangcell);
                    }
                }
            }
            curRoomNo++;
            rooms.push_back(room);
        }
    }
}
void Floor::nextFloor() {
    game->nextFloor();
}

std::ostream &operator<<(std::ostream &out, Floor &floor) {
    std::vector<std::vector<Cell*>>& cells = floor.getCells();
    for(int i =0;i < floor.getHeight();i ++){
        for(int j =0;j < floor.getWidth();j ++){
            Cell* cell = cells[i][j];
            cell->print(out);
        }
        out << std::endl;
    }

   Player* player = floor.getPlayer();
    out << "Race: " << player->name() << " Gold: " << player->getGold() <<  std::setw(50)<< "Floor " << floor.getLevel() << std::endl;
    out << "HP: " << player->getHpValue() << std::endl;
    out << "Atk: " << player->getAtkValue()->value() << std::endl;

    out << "Def: " << player->getDefValue()->value() << std::endl;
    out << "Action: ";
        player->printAction(out);
    for(int i =0;i < floor.getHeight();i ++){
        for(int j =0;j < floor.getWidth();j ++){
            Cell* cell = cells[i][j];
            Enemy* enemy = cell->getEnemy();
            if(enemy!= nullptr){
                enemy->printAction(out);
            }
        }
    }
    out << std::endl;
    return out;
}

Floor::~Floor() {
    player = nullptr;
    game = nullptr;
    removeAllCell();
}

void Floor::resetAllCellState() {
    for(int i =0;i < getHeight();i ++){
        for(int j =0;j < getWidth();j ++){
            Cell* cell = cells[i][j];
            cell->reset();
        }
    }
}
void Floor::removeAllCell() {
    for(int i =0;i < cells.size();i ++){
        std::vector<Cell*> line = cells[i];
        for(int j =0;j < line.size();j ++){
            Cell* cell = line[j];
            cell->reset();
            delete cell;
        }
    }
    cells.clear();
    blockCells.clear();
    rooms.clear();
}
