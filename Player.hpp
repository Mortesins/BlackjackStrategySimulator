#ifndef PLAYER_HPP
#define PLAYER_HPP

using namespace std;

#include <vector>
#include <string>

#include "Strategy/Strategy.hpp"

class Player 
{
  private:
    const string name;
    unsigned money;
    const vector <vector <unsigned short> > & cards;
    Strategy* strategy;
  public:
    Player(const vector < vector <unsigned short> > & c, string n);
/*** PRINTOUT CARDS ***\
    void prova();
\**********************/
    
    
    unsigned getBet(double trueCount);
    char getPlay(double trueCount, unsigned short dealerUpCard, unsigned handIndex);
    char getPlay(double trueCount, unsigned short dealerUpCard, unsigned handIndex, vector <char> actionsNotAllowed);
//  unsigned getInsurance(double trueCount);
    unsigned payMoney(unsigned m);

    int inPlay();
    
    void receiveMoney(unsigned m);
};

#endif
