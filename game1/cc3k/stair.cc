#include "stair.h"
#include "player.h"
#include "floor.h"
void Stair::accept(Player *& player){
        getFloor()->nextFloor();
}
