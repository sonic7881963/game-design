#ifndef PLAYERFACTORY_H
#define PLAYERFACTORY_H

#include "player.h"

class PlayerFactory {
public:
    Player* create(char c){
        switch (c) {
            case 'h':
                return createHuman();
            case 'd':
                return createDwarf();
            case 'e':
                return createElves();
            case 'o':
                return createOrc();
            default:
                return createHuman();
        }
    }
private:
    Human* createHuman() {
        return new Human (140, 20, 20);
    }

    Dwarf* createDwarf() {
        return new Dwarf (100, 20, 30);
    }

    Elves* createElves() {
        return new Elves (140, 30, 10);
    }

    Orc* createOrc() {
        return new Orc (180, 30, 25);
    }
};

#endif
