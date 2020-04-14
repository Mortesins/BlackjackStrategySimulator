#include <iostream>
#include "StrategyMultiplier.hpp"
#include "StrategySequence.hpp"

int main()
{
    /*** TEST PlayingStrategy ***/
    //PlayingStrategy a;
    //a.printStrategy();
    //std::vector<unsigned short> cards;
    //std::vector<char> actionsNotAllowed;
    //cards.push_back(1);
    //cards.push_back(4);
    //cards.push_back(2);
    //unsigned short dealerUpCard = '5';
    //actionsNotAllowed.push_back('D');
    //std::vector<unsigned short> coord = a.getCoordinates(cards,dealerUpCard);
    //std::cout << "(" << coord[0] << "," << coord[1] << ")" << std::endl;
    //std::cout << a.getPlay(cards,dealerUpCard,actionsNotAllowed) << std::endl;
    /****************************/

    //Strategy* mult = new StrategyMultiplier();
    //Strategy* seq = new StrategySequence();
    //std::cout << "prova" << std::endl;
    //std::cout << "multiplier: " << mult->getBet(1) << std::endl;
    //std::cout << "sequence: " << seq->getBet(1) << std::endl;
    Strategy* mult = new StrategyMultiplier();
    std::vector<unsigned short> cards;
    cards.push_back(1);
    cards.push_back(2);
    std::cout << mult->getPlay(1,cards,'5') << std::endl;
    std::cout << mult->getBet(2.1,18,1) << std::endl;
    return 0;
}
