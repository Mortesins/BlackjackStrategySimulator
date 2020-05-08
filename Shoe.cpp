#include "Shoe.hpp"

#include <cstdlib>
#include <ctime>
#include <sys/time.h>
#include <algorithm>

namespace
{
std::vector<unsigned short> generateOrderedDeck(unsigned numberOfDecks)
{
    std::vector<unsigned short> cardsToBeShuffled;
    cardsToBeShuffled.reserve(numberOfDecks*13*4);
    for (unsigned i=1; i <= 9; ++i)
    {
        for (unsigned j=0; j < numberOfDecks*4; ++j) // 4 cards per deck
        {
            cardsToBeShuffled.push_back(i);
        }
    }
    for (unsigned j=0; j < numberOfDecks*4*4; ++j) // 4 cards per deck but J,Q,K are all 10, so times 4
    {
        cardsToBeShuffled.push_back(10);
    }
    return cardsToBeShuffled;
}
}

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
    shuffleSpecifiedCards(generateOrderedDeck(numberOfDecks));
}

void Shoe::shuffleAndRemoveCards(const std::vector<unsigned short>& cardsToRemove)
{
    std::vector<unsigned short> cardsToShuffle = generateOrderedDeck(numberOfDecks);
    for (unsigned i = 0; i < cardsToRemove.size(); ++i)
    {
        std::vector<unsigned short>::iterator matchIndex =
                std::find(cardsToShuffle.begin(), cardsToShuffle.end(), cardsToRemove[i]);
        cardsToShuffle.erase(matchIndex);
    }
    shuffleSpecifiedCards(cardsToShuffle);
}

void Shoe::shuffleSpecifiedCards(std::vector<unsigned short> cardsToBeShuffled)
{
    cards.clear();
    unsigned numberOfCards = cardsToBeShuffled.size();
    cards.reserve(numberOfCards);
    /*** seed rand ***/
    timeval t1;
    gettimeofday(&t1, NULL);
    srand(t1.tv_usec * t1.tv_sec);
    /*****************/
    unsigned randomIndex;
    unsigned short pickedCard;

    for (unsigned short i=0; i < numberOfCards; ++i)
    {
        randomIndex = rand() % cardsToBeShuffled.size(); // random number from 0 to cardIndices.size() - 1
        pickedCard = cardsToBeShuffled[randomIndex];
        cardsToBeShuffled.erase(cardsToBeShuffled.begin() + randomIndex); // remove that card so I don't pick it again
        // pickedCard / 10 can be either 0 for 1 to 9 or 1 for 10, 11, 12, 13
        // I want pickedCard % 10 for 1 to 9, and 10 for 10, 11, 12, 13
        cards.push_back((pickedCard % 10) * (1 - pickedCard / 10) + ((pickedCard / 10) * 10));
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
