#ifndef STRATEGY_SEQUENCE_HPP
#define STRATEGY_SEQUENCE_HPP

using namespace std;

#include <vector>

#include "Strategy.hpp"

class StrategySequence
    : public Strategy
{
  private:
    vector <vector <unsigned int> > BettingStrategies;
    vector <unsigned int> levelCounters;
  public:
    StrategySequence();
    unsigned int getBet(double trueCount) const;
};

#endif
