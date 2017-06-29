#include "Strategy.hpp"

Strategy::Strategy()
    : stopStrategy()
{
    
}

char Strategy::getPlay(double trueCount, string playerHand, char dealerHand) const
{
    return '\0';
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
    
    Strategy* mult = new StrategyMultiplier();
    Strategy* seq = new StrategySequence();
    cout << "prova" << endl;
    cout << "multiplier: " << mult->getBet(1) << endl;
    cout << "sequence: " << seq->getBet(1) << endl;
    return 0;
}
