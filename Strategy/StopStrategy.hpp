#ifndef STOP_STRATEGY_HPP
#define STOP_STRATEGY_HPP

using namespace std;

#include <cmath>

class StopStrategy
{
  private:
    unsigned stopAt;
    unsigned numberOfLosses;
  public:
    StopStrategy();
    StopStrategy(unsigned stopAt);
    StopStrategy(unsigned stopAt, int numberOfLosses);
    StopStrategy(unsigned budget, float percentageOverBudget);
    StopStrategy(unsigned budget, double percentageOverBudget, unsigned numberOfLosses);
    virtual unsigned canPlaceBet(unsigned budget, unsigned bet, unsigned consecutiveLosses) const; //returns the bet
    virtual bool canSplit(unsigned budget, unsigned bet) const;
    virtual bool canDouble(unsigned budget, unsigned bet) const;
};

#endif
