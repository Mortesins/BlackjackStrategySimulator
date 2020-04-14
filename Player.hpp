#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>
#include <string>
// for ostream
#include <iostream>

#include "Action.hpp"
#include "Strategy/Strategy.hpp"
#include "PlayerSeat.hpp"

class PlayerSeat;

class Player
{
    friend ostream& operator<<(ostream& os,const Player& p);
  private:
    const string name;
    const PlayerSeat* playerSeat;
    unsigned money;
    Strategy* strategy;
  public:
    Player(string n, PlayerSeat* ps);
/*** PRINTOUT CARDS ***\
    void prova();
\**********************/


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

    int inPlay();

    unsigned payMoney(unsigned m);
    void receiveMoney(unsigned m);

/****************************/
    unsigned returnMoney();
/***************************/
};

#endif
