#ifndef STRATEGY_SEQUENCE_HPP
#define STRATEGY_SEQUENCE_HPP

using namespace std;

#include <vector>

#include "Strategy.hpp"

class StrategySequence
    : public Strategy
{
  private:
    vector <vector <unsigned> > BettingStrategies;
    vector <unsigned> levelCounters;
  public:
    StrategySequence();
    unsigned getBet(double trueCount, unsigned budget, unsigned bet, unsigned consecutiveLosses) const;
};

#endif
