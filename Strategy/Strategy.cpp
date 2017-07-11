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

char Strategy::getPlay(double trueCount, vector <unsigned short> cards, char dealerHand) const
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
    return playingStrategies[i]->getPlay(cards,dealerHand);
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
    //char dealerHand = '5';
    //actionsNotAllowed.push_back('D');
    //vector <unsigned short> coord = a.getCoordinates(cards,dealerHand);
    //cout << "(" << coord[0] << "," << coord[1] << ")" << endl;
    //cout << a.getPlay(cards,dealerHand,actionsNotAllowed) << endl;
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
    cout << mult->getBet(2.1,90,10,1) << endl;
    return 0;
}
