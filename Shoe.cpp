#include "Shoe.hpp"

Shoe::Shoe(unsigned short numberOfDecks, double penetration)
{
    this->numberOfDecks = numberOfDecks;
    this->unused = 52 * numberOfDecks * (1-penetration);
    shuffle();
}

void Shoe::shuffle()
{
    unsigned short tmp[13 * 4 * numberOfDecks];
    for (unsigned short i=0; i < 13*4*numberOfDecks; ++i)
        tmp[i] = 1 + (13 % i) ;
    srand(time(0));
    unsigned short r;
    unsigned short c;
    for (unsigned short i=0; i < 52*numberOfDecks; ++i)
    {
        r = rand() % 13 * 4 * numberOfDecks;
        c = tmp[r];
        if (c > 0)
        {
            cards.push_back((c % 10) * (1 - c / 10) + ((c / 10) * 10));
            tmp[r] = 0;
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
