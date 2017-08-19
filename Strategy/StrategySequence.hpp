#ifndef STRATEGY_SEQUENCE_HPP
#define STRATEGY_SEQUENCE_HPP

using namespace std;

#include <vector>

#include "Strategy.hpp"

class StrategySequence
    : public Strategy
{
  private:
    vector <vector <unsigned> > bettingStrategies;
    vector <unsigned> levelCounters;
  public:
    StrategySequence();
    unsigned getBet(double trueCount, unsigned budget, int streak);
};

#endif
