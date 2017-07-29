#include "Table.hpp"

Table::Table()
    : dealer(false),shoe(6,0.3)
{
   players.push_back(PlayerSeat());
   rules = new Rules();
   countingSystem = new CountingSystem();
}

bool Table::playersInPlay()
{
    bool inPlay = false;
    unsigned i = 0;
    while ( !inPlay && (i < players.size()) )
    {
        inPlay = players[i].player->inPlay();
        i++;
    }
    return inPlay;
}

void Table::placeBets()
{
    double trueCount = this->trueCount();
    unsigned bet;
    for (unsigned i = 0; i < players.size(); i++)
    {
        bet = players[i].player->getBet(trueCount);
        if (isMultipleOfBetSize(bet))
            players[i].pot[0] = bet;
        else
            throw "Table::placeBet: bet not multiple of betSize";
    }
}

void Table::distributeCards()
{

}

void Table::playersPlay()
{

}

void Table::playerPlay(unsigned playerIndex)
{

}

void Table::dealerPlay()
{

}

void Table::giveCollectMoney()
{

}

double Table::trueCount()
{
    return runningCount / shoe.decksRemaining();
}

bool Table::isMultipleOfBetSize(unsigned bet)
{
    return ( (bet % betSize) == 0 );
}

unsigned short Table::getCard()
{
    unsigned short card = shoe.getCard();
    runningCount += countingSystem->cardValue(card);
    return card;
}

void Table::playRound()
{
    if (playersInPlay())
    {
        placeBets();
        distributeCards();
        playersPlay();
        dealerPlay();
        giveCollectMoney();
    }
    else
    {
        // no players are playing
        return;
    }
}

