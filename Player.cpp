#include "Player.hpp"

#include "Strategy/StrategyMultiplier.hpp"

Player::Player(const vector < vector <unsigned short> > & c)
    : name("Test"),cards(c)
{
    strategy = new StrategyMultiplier();
}

unsigned Player::getBet(double trueCount)
{

}

char Player::getPlay(double trueCount, char dealerHand)
{
    
}

unsigned Player::getInsurance(double trueCount)
{
    
}

int Player::inPlay()
{
    
}

void Player::receiveMoney(unsigned money)
{
    
}

/*** PRINTOUT CARDS ***\
#include <iostream>
void Player::prova()
{
    cout << cards[0][0] << " " << cards[0][1] << " " << cards[0][2] << endl;
    cout << cards[1][0] << " " << cards[1][1] << endl;
}
\**********************/
