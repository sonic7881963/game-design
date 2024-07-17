#include <string>
#include "direction.h"
std::string dtoa(Direction direction){
    switch (direction) {
        case Direction::N:
            return "North";
        case Direction::NE:
            return "NorthEast";
        case Direction::E:
            return "East";
        case Direction::SE:
            return "SouthEast";
        case Direction::S:
            return "South";
        case Direction::SW:
            return "SouthWest";
        case Direction::W:
            return "West";
        default:
            return "NorthWest";
    }
};

Direction  itod( int no) {
    int i = no % 8;
    switch (i) {
        case 0:
            return Direction::N;
        case 1:
            return Direction::NE;
        case 2:
            return Direction::E;
        case 3:
            return Direction::SE;
        case 4:
            return Direction::S;
        case 5:
            return Direction::SW;
        case 6:
            return Direction::W;
        default:
            return Direction::NW;
    }
}

Direction  atod( std::string direction){
    if(direction == "no") {
        return Direction::N;
    }else if(direction == "so") {
        return Direction::S;

    }else if(direction == "ea") {
        return Direction::E;
    }else if(direction == "we") {
        return Direction::W;

    }else if(direction == "ne") {
        return Direction::NE;

    }else if(direction == "nw") {
        return Direction::NW;

    }else if(direction == "se") {
        return Direction::SE;

    }else {//} if(direction == "sw") {
        return Direction::SW;
    }
};
