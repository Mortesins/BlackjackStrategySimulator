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
    // cards is vector < vector <unsigned short> >, at the end of the round is emptied
        // so I need to add an empty "vector <unsigned short>" to which i will give the cards
    /*** add empty vector and give first card ***/
    vector <unsigned short> tmp;
    for (unsigned i = 0; i < players.size(); i++)
    {
        players[i].cards.push_back(tmp);
        players[i].cards[0].push_back(getCard());
    }
    /********************************************/
    
    // give card to dealer
    dealer.newCard(getCard());
    
    /*** give second card ***/
    for (unsigned i = 0; i < players.size(); i++)
    {
        players[i].cards[0].push_back(getCard());
    }
    /************************/
    
    // give second hole card to american dealer without counting it
    if (americanDealer)
        dealer.newCard(getCard(false));
}

void Table::playersPlay()
{
    for (unsigned i = 0; i < players.size(); i++)
    {
        playerPlay(i);
    }
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

unsigned short Table::getCard(bool countCard)
{ // no counting when giving second hole card to american dealer
    unsigned short card = shoe.getCard();
    if (countCard)
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

