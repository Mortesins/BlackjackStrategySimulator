#include "Strategy.hpp"
#include "BasicPlayingStrategy.hpp"
#include <iostream>

Strategy::Strategy()
    : stopStrategy()
{   //default
    name = "default";
    playingStrategy = new BasicPlayingStrategy();
}

unsigned Strategy::consecutiveLosses(int streak) // convert streak to consecutiveLosses
{
    if (streak >= 0)
    {
        return 0;
    }
    else
    {
        return streak * -1;
    }
}

bool Strategy::getInsurance(double trueCount)
{
    return trueCount > 3;
}

Action Strategy::getPlay(
    double trueCount,
    const std::vector<unsigned short>& cards,
    unsigned short dealerUpCard,
    std::vector<Action>& actionsNotAllowed,
    unsigned budget,
    unsigned bet
) const
{
    /*
     * actions not allowed passed as parameter should be filled based on Rules
     * this method then adds actions not allowed by budget, as dictated by StopStrategy methods (canSplit, canDouble)
     */
    if (!stopStrategy.canDouble(budget, bet))
    {
        actionsNotAllowed.push_back(Action::DOUBLEDOWN);
    }
    else if (!stopStrategy.canSplit(budget, bet))
    {
        actionsNotAllowed.push_back(Action::SPLIT);
    }

    return playingStrategy->getPlay(cards, dealerUpCard, actionsNotAllowed);
}

Action Strategy::getPlay(double trueCount, const std::vector<unsigned short>& cards, unsigned short dealerUpCard) const
{
    return playingStrategy->getPlay(cards, dealerUpCard);
}
