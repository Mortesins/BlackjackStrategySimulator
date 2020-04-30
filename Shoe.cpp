#include "Shoe.hpp"

#include <cstdlib>
#include <ctime>
#include <sys/time.h>
#include <algorithm>

Shoe::Shoe(unsigned numberOfDecks, double penetration)
{
    this->numberOfDecks = numberOfDecks;
    this->penetration = penetration;
    cards.reserve(numberOfDecks * 13 * 4);
    shuffle();
}

Shoe::Shoe(unsigned numberOfDecks, const std::vector<unsigned short>& cardsToRemove)
{
    this->numberOfDecks = numberOfDecks;
    this->penetration = penetration;
    shuffleAndRemoveCards(cardsToRemove);
}

void Shoe::shuffle()
{
    cards.clear();
    unsigned numberOfCards = 13*4*numberOfDecks;
    unsigned short orderedDecks[numberOfCards];
    std::vector<unsigned> cardIndices;
    cardIndices.reserve(numberOfCards);
    for (unsigned i=0; i < numberOfCards; ++i)
    {
        orderedDecks[i] = 1 + (i % 13);
        cardIndices.push_back(i);
    }
    /*** seed rand ***/
    timeval t1;
    gettimeofday(&t1, NULL);
    srand(t1.tv_usec * t1.tv_sec);
    /*****************/
    unsigned randomIndex;
    unsigned short pickedCard;

    for (unsigned short i=0; i < numberOfCards; ++i)
    {
        randomIndex = rand() % cardIndices.size(); // random number from 0 to cardIndices.size() - 1
        pickedCard = orderedDecks[cardIndices[randomIndex]]; // random card
        cardIndices.erase(cardIndices.begin() + randomIndex); // remove that index so I don't pick it again
        // pickedCard / 10 can be either 0 for 1 to 9 or 1 for 10, 11, 12, 13
        // I want pickedCard % 10 for 1 to 9, and 10 for 10, 11, 12, 13
        cards.push_back((pickedCard % 10) * (1 - pickedCard / 10) + ((pickedCard / 10) * 10));
    }
}

void Shoe::shuffleAndRemoveCards(const std::vector<unsigned short>& cardsToRemove)
{
    shuffle();
    for (unsigned i = 0; i < cardsToRemove.size(); ++i)
    {
        std::vector<unsigned short>::iterator matchIndex = std::find(cards.begin(), cards.end(), cardsToRemove[i]);
        cards.erase(matchIndex);
    }
}

unsigned short Shoe::getCard()
{
    unsigned short card = cards[cards.size()-1];
    cards.pop_back();
    return card;
}

double Shoe::decksRemaining()
{
    return cards.size() / 52.0;
}

unsigned Shoe::cardsRemaining()
{
    return cards.size();
}

bool Shoe::isFinished()
{
    return decksRemaining() < (1 - penetration);
}
