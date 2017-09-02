#ifndef PLAYER_HPP
#define PLAYER_HPP

using namespace std;

#include <vector>
#include <string>
// for ostream
#include <iostream>

#include "Strategy/Strategy.hpp"

class Player 
{
    friend ostream& operator<<(ostream& os,const Player& p);
  private:
    const string name;
    const vector <vector <unsigned short> > & cards;
    unsigned money;
    Strategy* strategy;
  public:
    Player(const vector < vector <unsigned short> > & c, string n);
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
};

#endif
