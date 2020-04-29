#ifndef STRATEGY_SEQUENCE_HPP
#define STRATEGY_SEQUENCE_HPP

using namespace std;

#include <vector>

#include "Strategy.hpp"

class StrategySequence
    : public Strategy
{
  private:
    std::vector<double> levels;
    std::vector<std::vector<unsigned> > bettingStrategies;
    std::vector<unsigned> levelCounters;
  public:
    StrategySequence();
    unsigned getBet(double trueCount, unsigned budget, int streak);
};

#endif
