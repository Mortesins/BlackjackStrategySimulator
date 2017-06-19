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
    vector <int> levels;
    vector <PlayingStrategy> playingStrategies;
  public:
    Strategy();
    char getPlay(unsigned int trueCount, string playerHand, char dealerHand) const;
    virtual unsigned int getBet(unsigned int trueCount) const = 0;    
};

#endif
