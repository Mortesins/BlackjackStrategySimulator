#include "DummyStrategy.hpp"
#include "../Constants.hpp"

unsigned DummyStrategy::getBet(double trueCount, unsigned budget, int streak)
{
    return this->stopStrategy.getBet(budget, MINIMUM_BET, consecutiveLosses(streak));
}
