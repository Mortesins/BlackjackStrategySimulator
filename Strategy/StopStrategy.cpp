#include "StopStrategy.hpp"

StopStrategy::StopStrategy(unsigned stopAt, int numberOfLosses)
{
    this->stopAt = stopAt;
    this->numberOfLosses = numberOfLosses;
}

StopStrategy::StopStrategy(unsigned budget, double percentageOverBudget, unsigned numberOfLosses)
{
    stopAt = (unsigned)round( budget * ( 1 + percentageOverBudget / 100.0 ) );
    this->stopAt = stopAt;
    this->numberOfLosses = numberOfLosses;
}

StopStrategy::StopStrategy()
{
    StopStrategy(80,2);
}

StopStrategy::StopStrategy(unsigned stopAt)
{
    StopStrategy(stopAt,2);
}

StopStrategy::StopStrategy(unsigned budget, float percentageOverBudget)
{
    StopStrategy(budget,percentageOverBudget,2);
}

unsigned StopStrategy::canPlaceBet(unsigned budget, unsigned bet, unsigned consecutiveLosses)
{
    if (budget < stopAt || consecutiveLosses == 0)
    {
        return bet;
    }
    else if (consecutiveLosses < numberOfLosses) // it's like consecutiveLosses == 1 when numberOfLosses=2
    {
        if (budget == stopAt)
            return 0; //stop
        else if (budget - bet < stopAt)
            return (budget - stopAt);
        else
            return bet;
    }
    else if (consecutiveLosses == numberOfLosses)
    {
        return 0; //stop
    }
    else
    {
        throw "StopStrategy::canPlaceBet";
    }
}

bool StopStrategy::canSplit(unsigned budget, unsigned bet)
{
    return true;
}
 
bool StopStrategy::canDouble(unsigned budget, unsigned bet)
{
    if (budget < stopAt)
        return true;
    else if (budget == stopAt || budget - bet < stopAt)
        return false;
    else
        return true;
}
