#include "Player.hpp"

#include "Strategy/StrategyMultiplier.hpp"
#include "PlayerSeat.hpp"
#include "Card.hpp"

Player::Player(string n, unsigned money, Strategy& s)
    : name(n), strategy(s)
{
    this->money = money;
}

void Player::assignPlayerSeat(PlayerSeat* ps)
{
    playerSeat = ps;
    return;
}

unsigned Player::getBet(double trueCount, int streak) const
{
    return strategy.getBet(trueCount, money, streak);
}

Action Player::getPlay(
    double trueCount,
    unsigned short dealerUpCard,
    unsigned handIndex,
    std::vector<Action>& actionsNotAllowed
) const
{
    unsigned bet = playerSeat->pot[handIndex];
    return strategy.getPlay(trueCount, playerSeat->cards[handIndex], dealerUpCard, actionsNotAllowed, money, bet);
}

unsigned Player::getInsurance(double trueCount, unsigned bet) const
{
    if (strategy.getInsurance(trueCount))
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

void Player::resetMoney(unsigned m)
{
    money = m;
}

unsigned Player::getMoney() const
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
                    os << card::toString(p.playerSeat->cards[i][j]) << "-";
                    j++;
                }
                if (p.playerSeat->cards[i].size() > 0)
                {
                    os << card::toString(p.playerSeat->cards[i][j]) << "\t\t";
                }
            }
        }
    }
    os << std::endl;
    return os;
}
