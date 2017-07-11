#include "Dealer.hpp"

void Dealer::updateHand()
{
    hand = 0;
    bool ace;
    for(unsigned short i = 0; i <= cards.size(); i++)
    {
        hand += cards[i];
        if (cards[i] == 0)
            ace = true;
    }
    if (hand <= 11 && ace == true)
        soft = true;
}

unsigned short Dealer::getHand()
{
    return hand;
}

unsigned short Dealer::upCard()
{
    return cards[0];
}

void Dealer::hit(unsigned short card)
{
    cards.push_back(card);
}
