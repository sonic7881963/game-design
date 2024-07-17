#ifndef GAME_H
#define GAME_H
#include <vector>

#include "floor.h"
#include "player.h"

class Game {
private:
    const int MAX_FLOORS = 5;
    Floor floor={1};
    Player* player = nullptr;
    std::string source;
    bool isNewLevel = false;
    void readMap();
    void createPlayer();
public:
    Game(std::string source):source(source){}
    bool checkIsOver();
    bool& getIsNewLevel(){return isNewLevel;}
    void start();
    void restart();
    void enemyAutoAct();
    void print();
    void newRound();
    virtual ~Game();

    Player *getPlayer();

    void nextFloor();
};


#endif
