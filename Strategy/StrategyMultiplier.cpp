#include "StrategyMultiplier.hpp"
#include "../Constants.hpp"
#include <cmath>

StrategyMultiplier::StrategyMultiplier()
    : Strategy()
{
    levels = {-2, 2};
    multipliers = {0, 1, 2};
}

unsigned StrategyMultiplier::getBet(double trueCount, unsigned budget, int streak)
{
    unsigned i = 0;
    bool found = false;
    while (!found && i < levels.size())
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
    return this->stopStrategy.getBet(budget, floor(multipliers[i]*MINIMUM_BET), consecutiveLosses(streak));
}
