#ifndef STRATEGY_SEQUENCE_HPP
#define STRATEGY_SEQUENCE_HPP

using namespace std;

#include <vector>

#include "Strategy.hpp"
#include "BettingStrategy.hpp"

class StrategySequence
    : public Strategy
{
  private:
    vector <BettingStrategy> BettingStrategies;
    vector <unsigned int> levelCounters;
  public:
    StrategySequence();
    unsigned int getBet(unsigned int trueCount) const;
};

#endif
