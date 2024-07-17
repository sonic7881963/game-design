#include "enemy.h"
#include "cell.h"
#include "barriersuit.h"
#include "gold.h"
#define ESC "\033["
#define COLOR "101"
#define YELLOW "43"
#define RED "41"
#define BLUE "44"
#define GREEN "42"
#define LIGHT_BLUE_BKG "106"
#define PURPLE_TXT "35"
#define RESET "\033[m"

Cell::Cell(int row,int col):row(row),col(col)
{
    this->access_range.resize(8);
    for(int i =0; i < 8; i++){
        this->access_range[i] = nullptr;
    }
}
void Cell::put(Potion* pPotion){
    this->item = pPotion;
    pPotion->getCell() = this;
};


void Cell::put(Stair *pStair) {
    pStair->getCell() = this;
    this->stair = pStair;
}


  void Cell:: put(BarrierSuit* bs) {
      bs->getCell() = this;
      this->item = bs;
      if (bs->getHoard() != nullptr) {
          std::vector<Cell *> &rangecells = this->getRangeCell();
          std::vector<Cell *> canacceptcells;
          for (Cell *c: rangecells) {
              if (c != nullptr && c->isBlock() && c->canPutMore()) {
                  canacceptcells.push_back(c);
              }
          }
          if (!canacceptcells.empty()) {
              canacceptcells[Shuffer::getLuckNum(canacceptcells.size())]->accept(bs->getHoard());
          }
      }
  }
 void Cell::put(Gold* pGold){
     this->gold = pGold;
     pGold->getCell() = this;
     if(pGold->getHoard() != nullptr){
         std::vector<Cell*>& rangecells = this->getRangeCell();
         std::vector<Cell*> canacceptcells;
         for(Cell* c : rangecells){
             if(c != nullptr && c->isBlock() && c->canPutMore()){
                 canacceptcells.push_back(c);
             }
         }
         if(!canacceptcells.empty()){
             canacceptcells[Shuffer::getLuckNum(canacceptcells.size())]->accept(pGold->getHoard());
         }

     }
 }


void Block::accept(Enemy *enemy) {
    if(!canAcceptEnemy()){
        return;
    }
    this->enemy = enemy;
    enemy->visit(this);

}
bool Cell::canAcceptPlayer(){
    return player == nullptr &&
           enemy == nullptr &&
           item == nullptr;
}


bool Block::accept(Player *player) {
    if (!canAcceptPlayer()) {
        return false;
    }
    if (gold != nullptr && gold->getHoard() != nullptr) {
        player->addAction("try use a gold with hoard");
        return false;
    }

    this->player = player;

    if (this->gold != nullptr) {

        this->gold->accept(player);
        this->gold = nullptr;
    }

    player->visit(this);

    if (this->stair != nullptr && this->stair->getVisible()) {
        this->stair->accept(player);
    }
    return true;
}

 void Cell::accept(Item* pItem){
    this->item = pItem;
     pItem->getCell() = this;
     for(Cell* c : this->getRangeCell()){
         if(c != nullptr &&  c->getPlayer() != nullptr){
             c->getPlayer()->addAction("sees a " + pItem->name() );
         }
     }
}

void Cell::reset() {
    this->player = nullptr;

    if(this->item != nullptr){
        delete item;
        this->item = nullptr;
    }
    if(this->enemy != nullptr){
        delete enemy;
        this->enemy = nullptr;
    }
    if(this->gold != nullptr){
        delete gold;
        this->gold = nullptr;
    }
    if(this->stair != nullptr){
        delete stair;
        this->stair = nullptr;
    }
}


// print
void Block::print(std::ostream &out) {
    if (isClear()) {
        out << '.';
    } else if (enemy != nullptr) {
        if(enemy->getCompass() != nullptr){
            out << ESC << RED << ";" << PURPLE_TXT <<"m"<< "&" << RESET;
        }else {
            out << ESC << RED << ";" << PURPLE_TXT << "m" << enemy->getDisplayChar() << RESET;
        }
    } else if (player != nullptr) {
        out << ESC << LIGHT_BLUE_BKG << ";" << PURPLE_TXT << "m" << "@" << RESET;
    } else if (item != nullptr) {
        out << item->getDisplayChar();
    } else if (stair != nullptr) {
        if (stair->getVisible()) {
            out << ESC << GREEN << ";" << PURPLE_TXT << "m" << stair->getDisplayChar() << RESET;
        } else {
            out << '.';
        }
    } else if (gold != nullptr) {
        out << ESC << COLOR << ";" << YELLOW << "m" << gold->getDisplayChar() << RESET;
    }
}


bool Door::accept(Player *player) {
    this->player = player;
    player->visit(this);
    return true;
}
void Door::print(std::ostream &out) {
    if ( player == nullptr) {
        out << '+';
    } else{
         out << ESC << LIGHT_BLUE_BKG << ";" << PURPLE_TXT <<"m"<< "@" << RESET;
    }
}
bool Passage::accept(Player *player) {
    this->player = player;
    player->visit(this);
    return true;
}
void Passage::print(std::ostream &out) {
    if ( player == nullptr) {
        out << '#';
    } else{
         out << ESC << LIGHT_BLUE_BKG << ";" << PURPLE_TXT <<"m"<< "@" << RESET;
    }
}
