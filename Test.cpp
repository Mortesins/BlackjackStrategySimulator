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
    unsigned long money = 0;
    std::vector<unsigned short> cardsToRemove = {dealerUpCard, playerCard1, playerCard2};

    Table t(print, 6, cardsToRemove); // 6 decks

    for (unsigned i = 0; i < numberOfSimulations; i++)
    {
        std::cout << "\t\t\tNumber: " << i << std::endl;
        money += t.playHandTest(dealerUpCard, playerCard1, playerCard2);
    }
    double averageMoney = money / (float)numberOfSimulations;
    double gain = (averageMoney - 1000) / 1000.0;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "Average money: " << averageMoney << " starting from 1000" << std::endl;
    std::cout << "Gain: " << gain << std::endl;
    return gain;
}

int main()
{
    testHand(1000000, 1, 1, 1);
    return 0;
}
