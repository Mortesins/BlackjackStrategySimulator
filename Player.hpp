#ifndef PLAYER_HPP
#define PLAYER_HPP

using namespace std;

#include <vector>
#include <string>
// for ostream
#include <iostream>

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
    char getPlay(double trueCount, unsigned short dealerUpCard, unsigned handIndex);
    char getPlay(double trueCount, unsigned short dealerUpCard, unsigned handIndex, vector <char> actionsNotAllowed, unsigned bet);
    unsigned getInsurance(double trueCount, unsigned bet);

    int inPlay();
    
    unsigned payMoney(unsigned m);
    void receiveMoney(unsigned m);
    
/****************************/
    unsigned returnMoney();
/***************************/
};

#endif
