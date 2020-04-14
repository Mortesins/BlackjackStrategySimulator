#include "Dealer.hpp"

Dealer::Dealer(bool softHit)
    :softHitFlag(softHit)
{
    cards.reserve(10);
    hand = 0;
}

unsigned short Dealer::getHand()
{
    return hand;
}

unsigned short Dealer::upCard()
{
    // TODO: throw if empty
    return cards[0];
}

unsigned short Dealer::holeCard()
{
    // TODO: throw if empty
    return cards[1];
}

bool Dealer::hit()
{
    return ( (hand < 17) || ( (isSoftHand) && (softHitFlag) && (hand == 17) ) );
}

void Dealer::newCard(unsigned short c)
{
    cards.push_back(c);
    if ( (c == 1) && (hand <= 10) )
    {
        isSoftHand = true;
        hand += 11;
    }
    else
    {
        hand += c;
    }
    if ( (isSoftHand) && (hand > 21) )
    {
        isSoftHand = false;
        hand -= 10;
    }
}

bool Dealer::blackjack()
{
    return ( (hand == 21) && (isSoftHand) );
}

void Dealer::reset()
{
    hand = 0;
    cards.clear();
}

std::ostream& operator<<(std::ostream& os, const Dealer& d)
{
    os << "Dealer:\t";
    unsigned i = 0;
    while (i < d.cards.size() - 1)
    {
        if (d.cards[i] == 1)
        {
            os << "A-";
        }
        else
        {
            os << d.cards[i] << "-";
        }
        ++i;
    }
    if (d.cards[i] == 1)
    {
        os << "A" << std::endl;
    }
    else
    {
        os << d.cards[i] << "\tHand Total:\t " << d.hand << std::endl;
    }
    return os;
}
