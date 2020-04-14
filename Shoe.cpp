#include "Shoe.hpp"

Shoe::Shoe(unsigned numberOfDecks, double penetration)
{
    this->numberOfDecks = numberOfDecks;
    this->penetration = penetration;
    shuffle();
}

Shoe::Shoe(unsigned numberOfDecks, const std::vector<unsigned short> & cardsToRemove)
{
    this->numberOfDecks = numberOfDecks;
    this->penetration = penetration;
    shuffleAndRemoveCards(cardsToRemove);
}

void Shoe::shuffleAndRemoveCards(const std::vector<unsigned short> & cardsToRemove)
{
    // empty deck
    cards.clear();
    /*** fill decks as usual ***/
    unsigned numberOfCards = 13*4*numberOfDecks;
    std::vector<unsigned short> tmp;
    for (unsigned i = 0; i < 13*4*numberOfDecks; ++i)
    {
        tmp.push_back(1 + (i % 13));
    }
    /***************************/
    /*** remove cards ***/
    unsigned j = 0;
    for (unsigned i = 0; i < cardsToRemove.size(); i++)
    {
        // find the card to remove
        while (cardsToRemove[i] != tmp[j] && j < tmp.size())
        {
            ++j;
        }
        // remove the card
        tmp.erase( tmp.begin() + j);
        --numberOfCards;
        j = 0; // restart searching from the beginning of the cards
    }
    /********************/
    /*** shuffle ***/
    timeval t1;
    gettimeofday(&t1, NULL);
    srand(t1.tv_usec * t1.tv_sec);
    unsigned r;
    unsigned short c;

    for (unsigned i=0; i < numberOfCards; ++i)
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
            --i;
        }
    }
    /***************/

    // remove the first card (end of deck)
    cards.erase(cards.begin() + cards.size() - 1);
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
    for (unsigned i=0; i < 13*4*numberOfDecks; ++i)
    {
        tmp[i] = 1 + (i % 13);
    }
    /*** seed rand ***/
    timeval t1;
    gettimeofday(&t1, NULL);
    srand(t1.tv_usec * t1.tv_sec);
    /*****************/
    unsigned r;
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
            --i;
        }
    }
    // remove the first card (end of deck)
    cards.erase(cards.begin() + cards.size() - 1);
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

/******************* TESTING *******************/
//#include <iostream>
//void Shoe::printDeck()
//{
    //unsigned i = 0;
    //while (i < cards.size() - 10)
    //{
        //for (unsigned j = 0; j < 10 - 1; j++)
        //{
            //std::cout << cards[i] << ",";
            //i++;
        //}
        //std::cout << cards[i] << std::endl;
        //i++;
    //}
    //while (i < cards.size() - 1)
    //{
        //std::cout << cards[i] << ",";
        //i++;
    //}
    //std::cout << cards[i] << std::endl;
//}
