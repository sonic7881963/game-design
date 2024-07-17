#include "game.h"
#include "playerfactory.h"
#include <sstream>
#include <fstream>
#include "enemy.h"
#include "shuffer.h"
using std::ostringstream;
using std::endl;
using std::ifstream;

void Game::readMap()  {
        ifstream in{source};
        if (in.fail()) {
            ostringstream oss;
            oss << "Unable to open file ";
            oss << source << " for reading." << std::endl;

        }
        in >> floor;

}
void Game::createPlayer(){
    std::cout << "Welcome to CC3K!" << std::endl;
    std::cout << "Please choose your race with specific letter to start the advature " << std::endl;
    std::cout << "or type any other letter to use default race." << std::endl;
    std::cout << std::endl << "(h).Human   (d).Dwarf   (e).Elves   (o).Orc" << std::endl;
    char cmd ;
    std::cin >> cmd;
    PlayerFactory playerFactory;
    player = playerFactory.create(cmd);
}
void Game::print() {
    std::cout << floor;
}

void  Game::start() {
    this->readMap();
    this->createPlayer();
    this->floor.getLevel() = Shuffer::getLuckNum(MAX_FLOORS-1)+1;
    this->floor.getPlayer() = player;
    this->floor.getGame() = this;
    this->floor.getLuckyLevel() = Shuffer::getLuckNum(MAX_FLOORS)+1;
    this->floor.spawn();
    isNewLevel = true;
}

void Game::restart() {
    delete this->player;
    start();
}

void Game::enemyAutoAct() {
    this->floor.enemyAutoAct();
}
void Game::newRound(){
    this->floor.newRound();
}

Game::~Game() {
    delete player;
}
bool Game::checkIsOver() {
    if (player->isDead()) {
        std::cout << "You are dead!" << std::endl;
        return true;
    } else  if (this->floor.getLevel() == MAX_FLOORS) {
        std::cout << "You win!" << std::endl;
        return true;
    }else{
        return false;
    }
}

Player *Game::getPlayer() {
    return player;
}

void Game::nextFloor() {
    floor.getLevel() ++;
    if(floor.getLevel() == MAX_FLOORS){
        return;
    }else {
        getIsNewLevel() = true;
        floor.resetAllCellState();
        player->enterFloor(floor);
        floor.spawn();
    }
}

