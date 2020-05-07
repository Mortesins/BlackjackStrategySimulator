#include "Table.hpp"
#include "Player.hpp"
#include "Constants.hpp"
#include "Strategy/StrategyMultiplier.hpp"
#include "Strategy/DummyStrategy.hpp"

#include <iostream>
#include <iomanip>

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

    unsigned const STARTING_MONEY = 20*MINIMUM_BET;
    DummyStrategy s;
    Player player("gigi", STARTING_MONEY, s);
    Table table({&player}, 6, print); // 6 decks
    for (unsigned i = 0; i < numberOfSimulations; i++)
    {
        std::cout << "\t\t\tNumber: " << i << std::endl;
        money += table.playRoundWithSpecificHandAndReturnPlayerBudget(dealerUpCard, playerCard1, playerCard2);
        player.resetMoney(STARTING_MONEY);
    }
    double averageMoney = money / double(numberOfSimulations);
    double gain = averageMoney - STARTING_MONEY;
    double gainPercentage =  gain / double(STARTING_MONEY) * 100;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "Average money: " << averageMoney << " starting from " << STARTING_MONEY << std::endl;
    std::cout << "Gain: " << gain << " percentage: " << std::setprecision(2) << gainPercentage << "%" <<std::endl;
    return gain;
}

void playMatch(const vector<Player*>& players)
{
    Table t(players, 6, true);
    while (t.playRound())
    {}
}

int main()
{
    testHand(100000, 1, 1, 1, false);
    return 0;
}
