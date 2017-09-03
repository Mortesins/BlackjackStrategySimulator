#include "Player.hpp"

#include "Strategy/StrategyMultiplier.hpp"

Player::Player(string n, PlayerSeat* ps)
    : name(n),playerSeat(ps)
{
    strategy = new StrategyMultiplier();
    money = 20;
}

unsigned Player::getBet(double trueCount, int streak)
{
    return strategy->getBet(trueCount,money,streak);
}

char Player::getPlay(double trueCount, unsigned short dealerUpCard, unsigned handIndex)     //dummy function, will be removed after Rules are implemented
{
    return strategy->getPlay(trueCount, playerSeat->cards[handIndex], dealerUpCard);
}

char Player::getPlay(double trueCount, unsigned short dealerUpCard, unsigned handIndex, vector <char>& actionsNotAllowed)
{
    unsigned bet = playerSeat->pot[handIndex];
    return strategy->getPlay(trueCount, playerSeat->cards[handIndex], dealerUpCard, actionsNotAllowed, money, bet);
}

unsigned Player::getInsurance(double trueCount, unsigned bet)
{
    if ( strategy->getInsurance(trueCount) )
        return bet*0.5; // half of the placed bet
    else
        return 0;
}

unsigned Player::payMoney(unsigned m)
{
    money -= m;
    return m;
}

int Player::inPlay()
{
    if (playerSeat->cards.size() == 0 && money < 2)
        return -1;
//  if (strategy.getBet() == 0)     /*disabled to keep playing and use up cards*/
//      return 0;
    else
        return 1;
}

void Player::receiveMoney(unsigned m)
{
    money += m;
}

unsigned Player::returnMoney()
{
    return money;
}

ostream& operator<<(ostream& os, const Player& p)
{
    os << "\tName:\t" << p.name << endl;
    os << "\tBudget:\t" << p.money << endl;
    os << "\tCards:\t";
    unsigned j = 0;
    for (unsigned i = 0; i < p.playerSeat->cards.size(); i++)
    {
        j = 0;
        if (p.playerSeat->cards[i].size() != 0)
        {
            while (j < (p.playerSeat->cards[i].size() - 1) ) // FOR SOME REASON THE WHILE LOOP COULD NOT CHECK SIZE() > 0 --> so the outer if was put
            {
                if (p.playerSeat->cards[i][j] == 1)
                    os << "A-";
                else
                    os << p.playerSeat->cards[i][j] << "-";
                j++;
            }
            if (p.playerSeat->cards[i].size() > 0)
            {
                if (p.playerSeat->cards[i][j] == 1)
                    os << "A\t\t";
                else
                    os << p.playerSeat->cards[i][j] << "\t\t";
            }
        }
    }
    os << endl;
    return os;   
}

/*** PRINTOUT CARDS ***\
#include <iostream>
void Player::prova()
{
    cout << cards[0][0] << " " << cards[0][1] << " " << cards[0][2] << endl;
    cout << cards[1][0] << " " << cards[1][1] << endl;
}
\**********************/
