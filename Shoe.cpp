#include "Shoe.hpp"

Shoe::Shoe(unsigned short numberOfDecks, double penetration)
{
    this->numberOfDecks = numberOfDecks;
    this->penetration = penetration;
    shuffle();
}

void Shoe::shuffle()
{
    /*** empty deck before refilling it ***/
    while (cards.size() > 0)
    {
        cards.pop_back();
    }
    /*** empty deck before refilling it ***/
    unsigned numberOfCards = 13*4*numberOfDecks;
    unsigned short tmp[numberOfCards];
    for (unsigned short i=0; i < 13*4*numberOfDecks; ++i)
        tmp[i] = 1 + (i % 13);
    srand(time(0));
    unsigned short r;
    unsigned short c;

    for (unsigned short i=0; i < numberOfCards; ++i)
    {
        r = rand() % numberOfCards; // random number from 0 to numberOfCards-1
        c = tmp[r]; // random card
        if (c > 0)
        {
            cards.push_back((c % 10) * (1 - c / 10) + ((c / 10) * 10));
            tmp[r] = 0;
        }
        else
        {
            i--;
        }
    }
    // remove first card of the deck
    cards.erase(cards.begin());
    
}

unsigned short Shoe::getCard()
{
    unsigned short card=cards[cards.size()-1];
    cards.pop_back();
    return card;
}

double Shoe::decksRemaining()
{
    return cards.size() / (float)(52);
}

unsigned Shoe::cardsRemaining()
{
    return cards.size();
}

bool Shoe::isFinished()
{
    return decksRemaining() < (1-penetration);
}
