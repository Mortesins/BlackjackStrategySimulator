#ifndef STRATEGY_MULTIPLIER_HPP
#define STRATEGY_MULTIPLIER_HPP

#include <vector>

#include "Strategy.hpp"

/**********************************************************************************************************************
 * StrategyMultiplier derives from Strategy and implements getBet, where the bets increase with multipliers based on a
 * range of true count levels. For a given true count, the corresponding multiplier is calculated and the bet is:
 *    2 * multiplier
 **********************************************************************************************************************/

class StrategyMultiplier
    : public Strategy
{
  private:
    std::vector<double> levels;
    std::vector<double> multipliers;
  public:
    StrategyMultiplier();
    virtual unsigned getBet(double trueCount, unsigned budget, int streak);
};

#endif
