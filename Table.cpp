#include "Table.hpp"

Table::Table()
    : dealer(false),shoe(6,0.3)
{
   players.push_back(PlayerSeat()); 
   players.push_back(PlayerSeat()); 
   rules = new Rules();
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

