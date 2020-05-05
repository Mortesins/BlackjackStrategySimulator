#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>
#include <string>
// for ostream
#include <iostream>

#include "Action.hpp"
#include "Strategy/Strategy.hpp"

class PlayerSeat;

class Player
{
    friend ostream& operator<<(ostream& os,const Player& p);
  private:
    const std::string name;
    const PlayerSeat* playerSeat;
    unsigned money;
    Strategy* strategy;
  public:
    Player(string n, PlayerSeat* ps);
    virtual ~Player();

    unsigned getBet(double trueCount, int streak);
    Action getPlay(
        double trueCount,
        unsigned short dealerUpCard,
        unsigned handIndex
    );
    Action getPlay(
        double trueCount,
        unsigned short dealerUpCard,
        unsigned handIndex,
        std::vector<Action>& actionsNotAllowed
    );
    unsigned getInsurance(double trueCount, unsigned bet);
    unsigned payMoney(unsigned m);
    void receiveMoney(unsigned m);
    unsigned getMoney();
};

#endif
