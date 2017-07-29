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
    bool playerBust = false;
    unsigned tc = this->trueCount();
    unsigned short dealerUpCard = dealer.upCard();
    // call getPlay (should give actionsAllowed here based on Rules)
    char play = players[playerIndex].player->getPlay(tc,dealerUpCard);
    switch(play)
    {
        /*** needs implementation 
        case 'R':
            // needs implementation
            break;
        ***/
        case 'P':
            split(playerIndex);
            break;
        case 'D':
            doubleDown(playerIndex);
            break;
        case 'H':
            players[playerIndex].cards[0].push_back(getCard());
            playerBust = checkPlayerBust(playerIndex);
            if (playerBust)
                return;
            break;
        case 'S':
            return;
    }
}

void Table::split(unsigned playerIndex)
{
    
}    

void Table::doubleDown(unsigned playerIndex)
{
    
}

bool Table::checkPlayerBust(unsigned playerIndex, unsigned handIndex)
{   // hand index choses on which hand to calculate the value (there can be more hands if split)
    unsigned handValue = 0;
    for (unsigned i = 0; i < players[playerIndex].cards[handIndex].size(); i++)
    {
        handValue += players[playerIndex].cards[handIndex][i];
    }
    if (handValue > 21)
    {   //bust
        /*** empty cards ***/
        while (players[playerIndex].cards[handIndex].size() > 0) 
        {
            handValue += players[playerIndex].cards[handIndex].pop_back();
        }
        /*******************/
        // remove money from pot
        players[playerIndex].pot[handIndex] = 0;
        return true;
    }
    return false;
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

