#ifndef STRATEGY_HPP
#define STRATEGY_HPP

using namespace std;

#include <vector>
#include <string>

#include "PlayingStrategy.hpp"

class Strategy
{
  private:
    string name;
    vector <double> levels;
    vector <PlayingStrategy*> playingStrategies;
  public:
    Strategy();
    char getPlay(double trueCount, string playerHand, char dealerHand) const;
    virtual unsigned int getBet(double trueCount) const = 0;    
};

#endif
