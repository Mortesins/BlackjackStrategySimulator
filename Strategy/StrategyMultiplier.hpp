#ifndef STRATEGY_MULTIPLIER_HPP
#define STRATEGY_MULTIPLIER_HPP

using namespace std;

#include <vector>

#include "Strategy.hpp"

class StrategyMultiplier
    : public Strategy
{
  private:
    vector <double> multipliers;
  public:
    StrategyMultiplier();
    unsigned getBet(double trueCount) const;
};

#endif
