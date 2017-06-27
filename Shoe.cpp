#include "Shoe.hpp"

Shoe::Shoe(unsigned short numberOfDecks, double penetration)
{
    this->numberOfDecks = numberOfDecks;
    this->unused = 52 * numberOfDecks * (1-penetration);
    shuffle();
}

void Shoe::shuffle()
{
    unsigned short tmp[13];
    for (unsigned short i=0; i<13; ++i)
        tmp[i] = 4 * numberOfDecks;
    srand(time(0));
    unsigned short r;
    for (unsigned short i=0; i < 52*numberOfDecks; ++i)
    {
        r = rand() % 13;
        if (tmp[r] > 0)
        {
            cards.push_back(((r+1) % 10) * (1 - (r+1) / 10) + ((r+1) / 10) * 10);
            tmp[r]--;
        }
        else{i--;}
    }
}

unsigned short Shoe::getCard()
{
    unsigned short card=cards[cards.size()];
    cards.pop_back();
    return card;
}

bool Shoe::isFinished()
{
    return cards.size() > unused;
}
