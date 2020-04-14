#include "Rules.hpp"

Rules::Rules()
{
    aces = false;
    handsAfterAceSplit = 0;
    bjBjPush = true;
}

std::vector<Action> Rules::getActionsNotAllowed(const std::vector<std::vector<unsigned short>> & cards, unsigned handIndex)
{
    std::vector<Action> actionsNotAllowed;
    /*** static rules ***/
    actionsNotAllowed.push_back(Action::SURRENDER);
    /********************/

    if (aces) // whatever the handIndex, only stand allowed
    {   // previous hand were aces
        if (cards.size() == 2)
        {   // two hands so aces were split, so for the next two hands only stand allowed
            handsAfterAceSplit++;
            if (handsAfterAceSplit <= 2) // only two hands after aces
            {
                actionsNotAllowed.push_back(Action::SPLIT);
                actionsNotAllowed.push_back(Action::DOUBLEDOWN);
                actionsNotAllowed.push_back(Action::HIT);
                return actionsNotAllowed;
            }
            else
            { // third hand after ace split
                aces = false; // no more aces, continue on to see other actions not allowed
                handsAfterAceSplit = 0;
            }
        }
        else
        {   // not split so no more aces, continue on to see other actions not allowed
            aces = false;
            handsAfterAceSplit = 0;
        }
    }
    if (cards[handIndex][0] == 1 && cards[handIndex][1] == 1)
    {   // aces
        aces = true;
        return actionsNotAllowed;
    }
    if (cards[handIndex].size() > 2)
    {   // no double down
        actionsNotAllowed.push_back(Action::DOUBLEDOWN);
    }
    if (cards.size() == 4)
    {   // no more splits
        actionsNotAllowed.push_back(Action::SPLIT);
    }
    return actionsNotAllowed;
}

bool Rules::blackjackBlackjackPush()
{
    return bjBjPush;
}
