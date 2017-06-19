#include "Strategy.hpp"

Strategy::Strategy()
{
    
}

char Strategy::getPlay(double trueCount, string playerHand, char dealerHand) const
{
    
}





#include <iostream>
#include "StrategyMultiplier.hpp"
#include "StrategySequence.hpp"
int main()
{
    Strategy* mult = new StrategyMultiplier();
    Strategy* seq = new StrategySequence();
    cout << "prova" << endl;
    cout << "multiplier: " << mult->getBet(1) << endl;
    cout << "sequence: " << seq->getBet(1) << endl;
    return 0;
}
