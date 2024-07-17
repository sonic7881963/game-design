#include <iostream>
#include "game.h"
#include "playerfactory.h"
int main() {

    Game g("./board.txt");
    g.start();
    g.print();
    Player* player = g.getPlayer();
    
    std::string move;
    while(std::cin >> move) {
         std::cout << "\033[2J\033[1;1H";
        g.newRound();
        if(move == "no") {
            player->move(Direction::N);
        }else if(move == "so") {
            player->move(Direction::S);
        }else if(move == "ea") {

            player->move(Direction::E);
        }else if(move == "we") {
            player->move(Direction::W);
        }else if(move == "ne") {
            player->move(Direction::NE);
        }else if(move == "nw") {
            player->move(Direction::NW);
        }else if(move == "se") {
            player->move(Direction::SE);
        }else if(move == "sw") {
            player->move(Direction::SW);
        }else if(move == "u") {
            std::string direction;
            std::cin >> direction;
            player->use(atod(direction));
        }else if(move == "a") {
            std::string direction;
            std::cin >> direction;
            player->attack(atod(direction));
        }else if(move == "r") {
            g.restart();
            player = g.getPlayer();
        }else if(move == "q") {
            return 0;
        }else if(move == "test") {
            player->getHpValue() = 9999999;
            player->getAtkValue()->base()->getNum() = 9999999;
            player->getDefValue()->base()->getNum() = 9999999;
        }

        if (g.getIsNewLevel()) {
            g.getIsNewLevel() = false;
        }else{
            g.enemyAutoAct();
        }
        g.print();
        if(g.checkIsOver()) {
            std::cout << "Your score is " << player->getGold() << std::endl;
            std::cout << "Do you want to restart the game(y/n)? " << std::endl;
            char order;
            std::cin >> order;
            if (order == 'y') {
                g.restart();
            }else {
                return 0;
            }
        }
    }

    return 0;
}
