#ifndef STRATEGY_HPP
#define STRATEGY_HPP

using namespace std;

#include <vector>
#include <string>

#include "PlayingStrategy.hpp"
#include "StopStrategy.hpp"

class Strategy
{
  private:
    string name;
    vector <double> levels;
    vector <PlayingStrategy*> playingStrategies;
    StopStrategy stopStrategy;
  public:
    Strategy();
    char getPlay(double trueCount, string playerHand, char dealerHand) const;
    virtual unsigned getBet(double trueCount) const = 0;    
};

#endif
