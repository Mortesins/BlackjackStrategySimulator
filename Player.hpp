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
    Player(const vector < vector <unsigned short> > & c);
/*** PRINTOUT CARDS ***\
    void prova();
\**********************/
    
    
    unsigned getBet(double trueCount);
    char getPlay(double trueCount, unsigned short dealerUpCard);
    char getPlay(double trueCount, unsigned short dealerUpCard, vector <char> actionsNotAllowed);
    unsigned getInsurance(double trueCount);
    unsigned getMoney(unsigned money);

    int inPlay();
    
    void receiveMoney(unsigned money);
};

#endif
