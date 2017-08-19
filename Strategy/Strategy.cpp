#include "Strategy.hpp"

#include <iostream>

Strategy::Strategy() 
    : stopStrategy()
{   //default
    name = "default";
    levels.push_back(-2);
    levels.push_back(2);
    /*******************/
    levels.push_back(4);
    levels.push_back(6);
    /*******************/
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

bool getInsurance(double trueCount)
{
    return trueCount > 3;
}

char Strategy::getPlay(double trueCount, const vector <unsigned short>& cards, unsigned short dealerUpCard, vector <char> actionsNotAllowed, unsigned budget, unsigned bet) const
{       
        // actions not allowed passed as parameter should be filled based on Rules
        // this method then adds actions not allowed by budget, as dictated by StopStrategy methods (canSplit, canDouble)
    unsigned i = 0;
    bool found = false;
    
    while (!found && i < playingStrategies.size())
    {
        if (trueCount > levels[i])
            i++;
        else
            found = true;
    }
    
    if (!stopStrategy.canDouble(budget,bet))
        actionsNotAllowed.push_back('D');
    else if (!stopStrategy.canSplit(budget,bet))
        actionsNotAllowed.push_back('P');
        
    return playingStrategies[i]->getPlay(cards,dealerUpCard,actionsNotAllowed);
}

char Strategy::getPlay(double trueCount, const vector <unsigned short>& cards, unsigned short dealerUpCard) const
{
    unsigned i = 0;
    bool found = false;
    
    while (!found && i < playingStrategies.size())
    {
        if (trueCount > levels[i])
            i++;
        else
            found = true;
    }
    return playingStrategies[i]->getPlay(cards,dealerUpCard);
}



#include <iostream>
#include "StrategyMultiplier.hpp"
#include "StrategySequence.hpp"

int main()
{
    /*** TEST PlayingStrategy ***/
    //PlayingStrategy a;
    //a.printStrategy();
    //vector <unsigned short> cards;
    //vector <char> actionsNotAllowed;
    //cards.push_back(1);
    //cards.push_back(4);
    //cards.push_back(2);
    //unsigned short dealerUpCard = '5';
    //actionsNotAllowed.push_back('D');
    //vector <unsigned short> coord = a.getCoordinates(cards,dealerUpCard);
    //cout << "(" << coord[0] << "," << coord[1] << ")" << endl;
    //cout << a.getPlay(cards,dealerUpCard,actionsNotAllowed) << endl;
    /****************************/
    
    //Strategy* mult = new StrategyMultiplier();
    //Strategy* seq = new StrategySequence();
    //cout << "prova" << endl;
    //cout << "multiplier: " << mult->getBet(1) << endl;
    //cout << "sequence: " << seq->getBet(1) << endl;
    Strategy* mult = new StrategyMultiplier();
    vector <unsigned short> cards;
    cards.push_back(1);
    cards.push_back(2);
    cout << mult->getPlay(1,cards,'5') << endl;
    cout << mult->getBet(2.1,18,1) << endl;
    return 0;
}
