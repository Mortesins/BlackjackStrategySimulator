#include "Table.hpp"

#include <iostream>

double testHand(
    unsigned numberOfSimulations,
    unsigned short dealerUpCard,
    unsigned short playerCard1,
    unsigned short playerCard2,
    bool print=false
)
{   // returns profit, percent from starting budget
    unsigned long long money = 0;
    std::vector<unsigned short> cardsToRemove = {dealerUpCard, playerCard1, playerCard2};

    for (unsigned i = 0; i < numberOfSimulations; i++)
    {
        Table t(print, 6); // 6 decks
        std::cout << "\t\t\tNumber: " << i << std::endl;
        money += t.playRoundWithSpecificHandAndReturnPlayerBudget(dealerUpCard, playerCard1, playerCard2);
    }
    double averageMoney = money / (float)numberOfSimulations;
    double gain = (averageMoney - 20) / 20.0;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "Average money: " << averageMoney << " starting from 20" << std::endl;
    std::cout << "Gain: " << gain << std::endl;
    return gain;
}

void playMatch()
{
    Table t(true, 6);
    while (t.playRound())
    {}
}

int main()
{
    testHand(10000, 1, 1, 1, true);
    return 0;
}
