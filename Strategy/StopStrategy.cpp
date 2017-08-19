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
    this->stopAt = 16;
    this->numberOfLosses = 2;
}

StopStrategy::StopStrategy(unsigned stopAt)
{
    this->stopAt = stopAt;
    this->numberOfLosses = 2;
}

StopStrategy::StopStrategy(unsigned budget, float percentageOverBudget)
{
    stopAt = (unsigned)round( budget * ( 1 + percentageOverBudget / 100.0 ) );
    this->stopAt = stopAt;
    this->numberOfLosses = 2;
}

unsigned StopStrategy::canPlaceBet(unsigned budget, unsigned bet, unsigned consecutiveLosses) const
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

bool StopStrategy::canSplit(unsigned budget, unsigned bet) const
{
    return true;
}
 
bool StopStrategy::canDouble(unsigned budget, unsigned bet) const
{
    if (budget < stopAt)
        return true;
    else if (budget == stopAt || budget - bet < stopAt)
        return false;
    else
        return true;
}
