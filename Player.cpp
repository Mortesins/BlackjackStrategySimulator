#include "Player.hpp"

#include "Strategy/StrategyMultiplier.hpp"

Player::Player(const vector < vector <unsigned short> > & c, string n)
    : name(n),cards(c)
{
    strategy = new StrategyMultiplier();
}

unsigned Player::getBet(double trueCount, int streak)
{
    return strategy->getBet(trueCount,money,streak);
}

char Player::getPlay(double trueCount, unsigned short dealerUpCard, unsigned handIndex)     //dummy function, will be removed after Rules are implemented
{
    return strategy->getPlay(trueCount, cards[handIndex], dealerUpCard);
}

char Player::getPlay(double trueCount, unsigned short dealerUpCard, unsigned handIndex, vector <char> actionsNotAllowed, unsigned bet)
{
    return strategy->getPlay(trueCount, cards[handIndex], dealerUpCard, actionsNotAllowed, money, bet);
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
    return money -= m;
}

int Player::inPlay()
{
    if (cards.size() == 0 && money < 2)
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



/*** PRINTOUT CARDS ***\
#include <iostream>
void Player::prova()
{
    cout << cards[0][0] << " " << cards[0][1] << " " << cards[0][2] << endl;
    cout << cards[1][0] << " " << cards[1][1] << endl;
}
\**********************/
