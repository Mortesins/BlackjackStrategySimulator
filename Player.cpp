#include "Player.hpp"

#include "Strategy/StrategyMultiplier.hpp"

Player::Player(const vector < vector <unsigned short> > & c, string n)
    : name(n),cards(c)
{
    strategy = new StrategyMultiplier();
}

unsigned Player::getBet(double trueCount, int streak)
{
    bet = strategy.getBet(trueCount,money,streak);
}

char Player::getPlay(double trueCount, unsigned short dealerUpCard, unsigned handIndex)     //dummy function, will be removed after Rules are implemented
{
    vector <char> actionsNotAllowed;
    return getPlay(trueCount, dealerUpCard, handIndex, actionsNotAllowed);
}

char Player::getPlay(double trueCount, unsigned short dealerUpCard, unsigned handIndex, vector <char> actionsNotAllowed);
{
    return strategy.getPlay(trueCount, dealerUpCard, handIndex, actionsNotAllowed);
}

/*
unsigned Player::getInsurance(double trueCount)
{
    
}
*/

void Player::payMoney(unsigned m)
{
    money -= m;
}

int Player::inPlay()
{
    if (cards.length() == 0 && money < 2)
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
