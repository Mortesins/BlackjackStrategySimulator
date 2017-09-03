#include "Rules.hpp"

Rules::Rules()
{
    aces = false;
    handsAfterAceSplit = 0;
    bjBjPush = true;
}

vector <char> Rules::getActionsNotAllowed(const vector <vector <unsigned short> > & cards, unsigned handIndex)
{
    vector <char> actionsNotAllowed;
    /*** static rules ***/
    actionsNotAllowed.push_back('R');
    /********************/
    
    if (aces) // whatever the handIndex, only stand allowed
    {   // previous hand were aces
        if (cards.size() == 2)
        {   // two hands so aces were split, so for the next two hands only stand allowed
            handsAfterAceSplit++;
            if (handsAfterAceSplit <= 2) // only two hands after aces
            {
                actionsNotAllowed.push_back('P');
                actionsNotAllowed.push_back('D');
                actionsNotAllowed.push_back('H');
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
        actionsNotAllowed.push_back('D');
    }
    if (cards.size() == 4)
    {   // no more splits
        actionsNotAllowed.push_back('P');
    }
    return actionsNotAllowed;
}

bool Rules::blackjackBlackjackPush()
{
    return bjBjPush;
}
