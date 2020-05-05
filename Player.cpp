#include "Player.hpp"

#include "Strategy/StrategyMultiplier.hpp"
#include "PlayerSeat.hpp"
#include "Constants.hpp"

Player::Player(string n, PlayerSeat* ps)
    : name(n), playerSeat(ps)
{
    strategy = new StrategyMultiplier();
    money = 20*MINIMUM_BET;
}

Player::~Player()
{
    delete strategy;
}

unsigned Player::getBet(double trueCount, int streak)
{
    return strategy->getBet(trueCount, money, streak);
}

Action Player::getPlay(double trueCount, unsigned short dealerUpCard, unsigned handIndex)     //dummy function, will be removed after Rules are implemented
{
    return strategy->getPlay(trueCount, playerSeat->cards[handIndex], dealerUpCard);
}

Action Player::getPlay(
    double trueCount,
    unsigned short dealerUpCard,
    unsigned handIndex,
    std::vector<Action>& actionsNotAllowed
)
{
    unsigned bet = playerSeat->pot[handIndex];
    return strategy->getPlay(trueCount, playerSeat->cards[handIndex], dealerUpCard, actionsNotAllowed, money, bet);
}

unsigned Player::getInsurance(double trueCount, unsigned bet)
{
    if (strategy->getInsurance(trueCount))
    {
        return bet*0.5; // half of the placed bet
    }
    else
    {
        return 0;
    }
}

unsigned Player::payMoney(unsigned m)
{
    money -= m;
    return m;
}

void Player::receiveMoney(unsigned m)
{
    money += m;
}

unsigned Player::getMoney()
{
    return money;
}

ostream& operator<<(ostream& os, const Player& p)
{
    os << "\tName:\t" << p.name << std::endl;
    os << "\tBudget:\t" << p.money << std::endl;
    if (p.playerSeat->cards.size() > 0)
    {
        os << "\tCards:\t";
        unsigned j = 0;
        for (unsigned i = 0; i < p.playerSeat->cards.size(); ++i)
        {
            j = 0;
            if (p.playerSeat->cards[i].size() != 0)
            {
                while (j < (p.playerSeat->cards[i].size() - 1) ) // FOR SOME REASON THE WHILE LOOP COULD NOT CHECK SIZE() > 0 --> so the outer if was put
                {
                    if (p.playerSeat->cards[i][j] == 1)
                    {
                        os << "A-";
                    }
                    else
                    {
                        os << p.playerSeat->cards[i][j] << "-";
                    }
                    j++;
                }
                if (p.playerSeat->cards[i].size() > 0)
                {
                    if (p.playerSeat->cards[i][j] == 1)
                    {
                        os << "A\t\t";
                    }
                    else
                    {
                        os << p.playerSeat->cards[i][j] << "\t\t";
                    }
                }
            }
        }
    }
    os << std::endl;
    return os;
}
