#include "Dealer.hpp"
#include "Card.hpp"

Dealer::Dealer(bool softHit)
    :softHitFlag(softHit)
{
    cards.reserve(10);
    hand = 0;
    isSoftHand = false;
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

bool Dealer::canMakeBlackjack()
{
    return (cards[0] == 10 || cards[0] == 1);
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
        os << card::toString(d.cards[i]) << "-";
        ++i;
    }
    os << card::toString(d.cards[i]);
    os << "\tHand Total:\t " << d.hand << std::endl;
    return os;
}
