
#ifndef TRADESKILL_H
#define TRADESKILL_H

class Player;
class Trader {
protected:
    Player* trader;
public:
    Trader( Player* trader):trader(trader){}
    virtual int buy(int gold)=0;
    virtual ~Trader(){};
};

class TraderNormal:public Trader{
public:
    TraderNormal( Player* trader):Trader(trader){}
    virtual int buy(int gold){return gold;};
};

class TraderWorthDouble:public Trader{
public:
    TraderWorthDouble( Player* trader):Trader(trader){}
    virtual int buy(int gold){return gold/2;};
};

class TraderWorthHalf:public Trader{
public:
    TraderWorthHalf( Player* trader):Trader(trader){}
    virtual int buy(int gold){return gold*2;};
};
#endif

