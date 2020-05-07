#include "Table.hpp"
#include "Player.hpp"
#include "Constants.hpp"
#include "Action.hpp"
#include "Card.hpp"
#include "Strategy/DummyStrategy.hpp"

#include "include/cxxopts.hpp"
#include <iostream>
#include <iomanip>
#include <fstream>

void testHand(
    unsigned numberOfSimulations,
    unsigned short dealerUpCard,
    unsigned short playerCard1,
    unsigned short playerCard2,
    Action firstAction,
    bool print=false,
    bool progression=true,
    std::string csvFileName="",
    bool silent=false
)
{   // returns profit, percent from starting budget
    std::vector<unsigned short> cardsToRemove = {dealerUpCard, playerCard1, playerCard2};
    unsigned nWins = 0;
    unsigned nLoss = 0;
    unsigned nDraw = 0;
    unsigned long long winsSum = 0;
    unsigned long long lossSum = 0;
    int money = 0;
    int delta = 0;

    unsigned const STARTING_MONEY = 20*MINIMUM_BET;
    DummyStrategy s;
    Player player("gigi", STARTING_MONEY, s);
    Table t({&player}, 6, print); // 6 decks
    for (unsigned i = 0; i < numberOfSimulations; i++)
    {
        if (progression && i % 1000 == 0)
        {
            std::cout << "\t\t\tNumber: " << i << std::endl;
        }
        money = t.playRoundWithSpecificHandAndReturnPlayerBudget(dealerUpCard, playerCard1, playerCard2, firstAction);
        delta = money - STARTING_MONEY;
        if (delta > 0)
        {
            winsSum += delta;
            ++nWins;
        }
        else if (delta < 0)
        {
            lossSum -= delta;
            ++nLoss;
        }
        else
        {
            ++nDraw;
        }
        player.resetMoney(STARTING_MONEY);
    }
    double averageWin = winsSum / double(numberOfSimulations);
    double averageWinPercentage = averageWin / double(STARTING_MONEY) * 100;
    double averageLoss = lossSum / double(numberOfSimulations);
    double averageLossPercentage = averageLoss / double(STARTING_MONEY) * 100;
    double averageMoney = averageWin - averageLoss + STARTING_MONEY;
    double gain = averageMoney - STARTING_MONEY;
    double gainPercentage =  gain / double(STARTING_MONEY) * 100;
    double winPercentage = nWins / double(numberOfSimulations) * 100;
    double lossPercentage = nLoss / double(numberOfSimulations) * 100;
    double drawPercentage = nDraw / double(numberOfSimulations) * 100;
    if (csvFileName != "")
    {
        ofstream outputfile;
        outputfile.open(csvFileName, ios::app);
        outputfile << gain << "," << averageWin << "," << averageLoss << "," << winPercentage << "," << lossPercentage
                    << "," << drawPercentage << std::endl;
        outputfile.close();
    }
    if (!silent)
    {
        std::cout << "DealerUpCard: " << dealerUpCard
                        << " playerHand: " << card::toString(playerCard1) << "-"  << card::toString(playerCard2)
                        << " action: " << action::toChar(firstAction)
                        << " number of simulations: " << numberOfSimulations << std::endl;
        std::cout << "Average money: " << averageMoney << " starting from " << STARTING_MONEY << std::endl;
        std::cout << "Average gain: " << gain
                        << " percentage: " << std::setprecision(2) << gainPercentage << "%" <<std::endl;
        std::cout << "Wins percentage: " << std::setprecision(2) << winPercentage << "%" <<std::endl;
        std::cout << "Loss percentage: " << std::setprecision(2) << lossPercentage << "%" <<std::endl;
        std::cout << "Draw percentage: " << std::setprecision(2) << drawPercentage << "%" <<std::endl;
        std::cout << "Average win: " << averageWin
                        << " percentage: " << std::setprecision(2) << averageWinPercentage << "%" <<std::endl;
        std::cout << "Average loss: " << averageLoss
                        << " percentage: " << std::setprecision(2) << averageLossPercentage << "%" <<std::endl;
    }
}

void playMatch(const vector<Player*>& players)
{
    Table t(players, 6, true);
    while (t.playRound())
    {}
}

int main(int argc, char** argv)
{
    cxxopts::Options options("singleHandTest", "Test a single blackjack hand with a specific action.");

    options.add_options()
        ("n", "Number of simulations", cxxopts::value<unsigned>())
        ("dealer-upcard", "Dealer's upcard", cxxopts::value<std::string>())
        ("player-hand", "Player's hand, must be lik A-A or 10-5 or 9-6", cxxopts::value<std::string>())
        ("action", "First player action. H=HIT, S=STAND, D=DOUBLEDOWN, P=SPLIT", cxxopts::value<char>())
        ("print", "Flag to enable printing of hands", cxxopts::value<bool>()->default_value("0"))
        ("progression", "Flag to enable printing of number of simulated hands every 1000 hands",
                        cxxopts::value<bool>()->default_value("0"))
        ("csv", "Filname where to write statistics", cxxopts::value<std::string>())
        ("silent", "When csv is specified, this flag completely turns off output on terminal",
                        cxxopts::value<bool>()->default_value("0"))
        ("h,help", "Print usage")
    ;

    auto result = options.parse(argc, argv);

    if (result.count("help") || !result.count("n") || !result.count("dealer-upcard") || !result.count("player-hand")
            || !result.count("action") )
    {
        std::cout << options.help() << std::endl;
        exit(0);
    }

    bool print = result["print"].as<bool>();
    bool progression = result["progression"].as<bool>();
    unsigned nSimulations = result["n"].as<unsigned>();
    Action action = action::fromChar(result["action"].as<char>());
    std::string playerHand = result["player-hand"].as<std::string>();
    std::string dealerUpCard = result["dealer-upcard"].as<std::string>();

    int dashPosition = playerHand.find('-');
    unsigned short playerCard1 = card::fromString(playerHand.substr(0, dashPosition));
    unsigned short playerCard2 = card::fromString(playerHand.substr(dashPosition+1));

    if (result.count("csv"))
    {
        std::string csvFileName = result["csv"].as<std::string>();
        bool silent = result["silent"].as<bool>();
        testHand(nSimulations, card::fromString(dealerUpCard), playerCard1, playerCard2, action, print, progression,
                csvFileName, silent);
    }
    else
    {
        testHand(nSimulations, card::fromString(dealerUpCard), playerCard1, playerCard2, action, print, progression);
    }

    return 0;
}
