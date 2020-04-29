#include "Rules.hpp"

Rules::Rules()
{
    aces = false;
    handsAfterAceSplit = 0;
    bjBjPush = true;
    actionsNotAllowedTemplate = {Action::SPLIT, Action::SURRENDER};
}

std::vector<Action> Rules::getActionsNotAllowed(
    const std::vector<std::vector<unsigned short>>& cards,
    unsigned handIndex
)
{
    // previous hand was aces
    if (aces)
    {
        // if two hands then it was split, so for the next hands only stand allowed
        if (cards.size() == 2)
        {
            ++handsAfterAceSplit;
            if (handsAfterAceSplit <= 2) // only two hands after aces
            {
                std::vector<Action> actionsNotAllowed =
                    {Action::HIT, Action::SPLIT, Action::DOUBLEDOWN, Action::SURRENDER};
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

    // check if it is splittable
    if (cards[handIndex][0] == cards[handIndex][1] && cards[handIndex].size() == 2 && cards.size() < 4)
    {
        if (cards[handIndex][0] == 1)
        {
            // aces
            aces = true;
        }
        std::vector<Action> actionsNotAllowed = actionsNotAllowedTemplate;
        actionsNotAllowed.erase(actionsNotAllowed.begin());  // Remove SPLIT
        return actionsNotAllowed;
    }
    // check if more than 2 cards, if so no double down
    if (cards[handIndex].size() > 2)
    {
        std::vector<Action> actionsNotAllowed = actionsNotAllowedTemplate;
        actionsNotAllowed.push_back(Action::DOUBLEDOWN);
        return actionsNotAllowed;
    }

    return actionsNotAllowedTemplate;
}

bool Rules::blackjackBlackjackPush()
{
    return bjBjPush;
}
