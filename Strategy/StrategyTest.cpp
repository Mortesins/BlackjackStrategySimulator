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
