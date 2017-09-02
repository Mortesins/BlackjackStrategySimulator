#include "Dealer.hpp"

Dealer::Dealer(bool softHit)
    :softhit(softHit)
{
    hand = 0;
}

unsigned short Dealer::getHand()
{
    return hand;
}

unsigned short Dealer::upCard()
{
    return cards[0];
}

unsigned short Dealer::holeCard()
{
    return cards[1];
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

void Dealer::reset()
{
    hand = 0;
    cards.clear();
}

ostream& operator<<(ostream& os, const Dealer& d)
{
    os << "Dealer:\t";
    unsigned i = 0;
    while (i < d.cards.size() - 1)
    {
        if (d.cards[i] == 1)
            os << "A-";
        else
            os << d.cards[i] << "-";
        i++;
    }
    if (d.cards[i] == 1)
        os << "A" << endl;
    else
        os << d.cards[i] << "\tHand Total:\t " << d.hand << endl;
    return os;
}
