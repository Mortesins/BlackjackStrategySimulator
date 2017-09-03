#include "Strategy.hpp"

#include <iostream>

Strategy::Strategy() 
    : stopStrategy()
{   //default
    name = "default";
    levels.push_back(-2);
    levels.push_back(2);
    PlayingStrategy* tmp = new PlayingStrategy();
    playingStrategies.push_back(tmp);
    playingStrategies.push_back(tmp);
    playingStrategies.push_back(tmp); // same playing strategy for all levels
}

unsigned Strategy::consecutiveLosses(int streak) // convert streak to consecutiveLosses
{
    if (streak >= 0)
        return 0;
    else
        return streak * -1;
}

bool Strategy::getInsurance(double trueCount)
{
    return trueCount > 3;
}

char Strategy::getPlay(double trueCount, const vector <unsigned short>& cards, unsigned short dealerUpCard, vector <char>& actionsNotAllowed, unsigned budget, unsigned bet) const
{       
        // actions not allowed passed as parameter should be filled based on Rules
        // this method then adds actions not allowed by budget, as dictated by StopStrategy methods (canSplit, canDouble)
    unsigned i = 0; // indexOfLevels
    unsigned j = 0; // indexOfPlayingStrategies
    bool found = false;
    
    while (!found && i < levels.size())
    {
        if (trueCount > levels[i])
            j++;
        else
            found = true;
        i++;
    }
    
    if (!stopStrategy.canDouble(budget,bet))
        actionsNotAllowed.push_back('D');
    else if (!stopStrategy.canSplit(budget,bet))
        actionsNotAllowed.push_back('P');
        
    return playingStrategies[j]->getPlay(cards,dealerUpCard,actionsNotAllowed);
}

char Strategy::getPlay(double trueCount, const vector <unsigned short>& cards, unsigned short dealerUpCard) const
{
    unsigned i = 0; // indexOfLevels
    unsigned j = 0; // indexOfPlayingStrategies
    bool found = false;
    
    while (!found && i < levels.size())
    {
        if (trueCount > levels[i])
            j++;
        else
            found = true;
        i++;
    }
    return playingStrategies[j]->getPlay(cards,dealerUpCard);
}
