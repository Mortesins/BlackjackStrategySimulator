#include "StopStrategy.hpp"
#include <cmath>

StopStrategy::StopStrategy(unsigned stopAtBudget, unsigned stopAtNumberOfLosses)
{
    this->stopAtBudget = stopAtBudget;
    this->stopAtNumberOfLosses = stopAtNumberOfLosses;
}

StopStrategy::StopStrategy(unsigned budget, double percentageOverBudget, unsigned stopAtNumberOfLosses)
    : StopStrategy::StopStrategy((unsigned) round(budget * (1 + percentageOverBudget / 100.0)), stopAtNumberOfLosses)
{}

StopStrategy::StopStrategy()
    : StopStrategy::StopStrategy(24, 2)
{}

unsigned StopStrategy::getBet(unsigned budget, unsigned bet, unsigned consecutiveLosses) const
{
    if (budget < stopAtBudget || consecutiveLosses == 0)
    {
        return bet;
    }
    else if (consecutiveLosses < stopAtNumberOfLosses) // it's like consecutiveLosses == 1 when stopAtNumberOfLosses=2
    {
        if (budget == stopAtBudget)
        {
            return 0; //stop
        }
        else if (budget - bet < stopAtBudget)
        {
            return (budget - stopAtBudget);
        }
        else
        {
            return bet;
        }
    }
    else if (consecutiveLosses >= stopAtNumberOfLosses)
    {
        return 0; //stop
    }
    else
    {
        throw "StopStrategy::getBet";
    }
}

bool StopStrategy::canSplit(unsigned budget, unsigned bet) const
{
    if (budget < stopAtBudget)
    {
        return true;
    }
    if (budget == stopAtBudget || budget - bet < stopAtBudget)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool StopStrategy::canDouble(unsigned budget, unsigned bet) const
{
    return canSplit(budget, bet);  // same logic
}
