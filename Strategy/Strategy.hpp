#ifndef STRATEGY_HPP
#define STRATEGY_HPP

using namespace std;

#include <vector>
#include <string>

#include "PlayingStrategy.hpp"
#include "StopStrategy.hpp"

class Strategy
{
  protected:
    string name;
    vector <double> levels;
    vector <PlayingStrategy*> playingStrategies;
    StopStrategy stopStrategy;
  public:
    Strategy();
    char getPlay(double trueCount, const vector <unsigned short>& cards, unsigned short dealerUpCard, vector <char> actionsNotAllowed, unsigned budget, unsigned bet) const;
    char getPlay(double trueCount, const vector <unsigned short>& cards, unsigned short dealerUpCard) const;
    virtual unsigned getBet(double trueCount, unsigned budget, unsigned bet, unsigned consecutiveLosses) = 0;    
};

#endif
