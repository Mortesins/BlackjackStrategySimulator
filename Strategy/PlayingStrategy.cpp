#include "PlayingStrategy.hpp"

#include <iostream>
#include <iomanip>


std::vector<unsigned short> PlayingStrategy::getCoordinates(
    const std::vector<unsigned short>& cards,
    unsigned short dealerUpCard
) const
{
    // first element row == player hand, second element column == dealerUpCard

    std::vector<unsigned short> coord{0, 0};
    /*** dealer hand ***/
    if (dealerUpCard == 1) // ace
    {
        coord[1] = 9; //last column
    }
    else
    {
        coord[1] = dealerUpCard - 2; // 2 is first column so 0
    }
    /*******************/
    /*** player hand ***/
    if (cards.size() == 2 && cards[0] == cards[1]) // pair
    {
        // 2-2 10, A-A 19
        if (cards[0] == 1) //ACE
        {
            coord[0] = 19;
        }
        else
        {
            coord[0] = 8 + cards[0]; // 2-2 --> 10
        }
    }
    else // no pair
    {
        bool aceFound = false;
        unsigned sum = 0;
        for (unsigned i = 0; i < cards.size(); ++i)
        {
            if (cards[i] == 1)
            {
                aceFound = true;
            }
            sum += cards[i];
        }
        // if soft hand
        if (aceFound && sum <= 11)
        {
            unsigned sumWithoutAce = sum - 1;
            if (sumWithoutAce == 10)
            {
                // A-10 is 21 so should not be called but I give A-9 coordinates
                coord[0] = 9;
            }
            else
            {
                coord[0] = sumWithoutAce + 18; // sumWithoutAce = 2 --> 20
            }
        }
        else
        {
            if (sum <= 8)
            {
                coord[0] = 0;
            }
            else if (sum >= 17)
            {
                coord[0] = 9;
            }
            else
            {
                coord[0] = sum - 8; // so if 9 --> 1 which is second row
            }
        }
    }
    /*******************/
    return coord;
}

void PlayingStrategy::printStrategy() const
{
    std::cout << "       2   3   4   5   6   7   8   9  10   A" << std::endl;
    for (unsigned i = 0; i < 10; ++i)
    {
        std::cout << std::setw(5) << i+8; // index 0 is hand of 8
        printActionRow(i);
    }
    std::cout << "--------------------------------------------" << std::endl;
    for (unsigned i=10; i < 20; ++i)
    {
        if (i == 19)
        {
            std::cout << std::setw(5) << "A-A";
        }
        else
        {
            std::string str = std::to_string(i-8) + "-" + std::to_string(i-8); // 10 is 2-2, 11 is 3-3
            std::cout << std::setw(5) << str;
        }
        printActionRow(i);
    }
    std::cout << "--------------------------------------------" << std::endl;
    for (unsigned i=20; i < 28; i++)
    {
        std::cout << "  A-" << i-18; // 20 is A-2
        printActionRow(i);
    }
}

inline void PlayingStrategy::printActionRow(unsigned row) const
{
    for (unsigned i = 0; i < 10; ++i)
    {
        std::cout << "  " << actionsTable[row][i][0];
        if (actionsTable[row][i].size() == 2 && actionsTable[row][i][1] == Action::STAND)
        {
            std::cout << "s";
        }
        else
        {
            std::cout << " ";
        }
    }
    std::cout << std::endl;
}
