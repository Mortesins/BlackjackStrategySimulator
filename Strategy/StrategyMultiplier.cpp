#include "StrategyMultiplier.hpp"

StrategyMultiplier::StrategyMultiplier()
    : Strategy()
{   // default, so the levels are TC [-2 | 2]
    multipliers.push_back(0);
    multipliers.push_back(1);
    multipliers.push_back(2);
}

unsigned StrategyMultiplier::getBet(double trueCount, unsigned budget, int streak)
{
    unsigned i = 0;
    bool found = false;

    while (!found && i < multipliers.size())
    {
        if (trueCount > levels[i])
        {
            ++i;
        }
        else
        {
            found = true;
        }
    }
    return this->stopStrategy.canPlaceBet(budget,floor(multipliers[i]*2),consecutiveLosses(streak));
}
