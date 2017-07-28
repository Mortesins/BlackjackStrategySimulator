#include "Dealer.hpp"

unsigned short Dealer::getHand()
{
    return hand;
}

unsigned short Dealer::upCard()
{
    return cards[0];
}

bool Dealer::hit()
{
    return ( (hand < 17) || ( (hand == 17) && (soft) && (softhit) ) );
}

void Dealer::newCard(unsigned short c)
{
    cards.push_back(c);
    hand += c;
    if ( (c == 1) && (hand <= 11) )
    {
        soft = true;
        hand += 10;
    }
    if ( (hand > 21) && (soft) )
    {
        soft = false;
        hand -= 10;
    }
}

bool Dealer::blackjack()
{
    return ( (hand == 21) && (soft) );
}
