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
        for (unsigned handIndex = 0; handIndex < players[i].cards.size(); handIndex++)
        {   // for each hand, NOTE: cards.size() should be changed by playerPlay when split
            playerPlay(i,handIndex);
        }
    }
}

void Table::playerPlay(unsigned playerIndex, unsigned handIndex)
{   // plays handIndex, if split continues to play the first hand of the split, which has same handIndex
    unsigned short dealerUpCard = dealer.upCard();
    
    bool playerBust;
    unsigned tc;
    
    
    char play;
    while (play != 'S') // until player stands
    {
        tc = this->trueCount();
        // call getPlay (should give actionsAllowed here based on Rules)
        play = players[playerIndex].player->getPlay(tc,dealerUpCard); //hand index
        switch(play)
        {
            /*** needs implementation 
            case 'R':
                // needs implementation
                break;
            ***/
            case 'P':
                split(playerIndex,handIndex);
                break; // continues play on the same handIndex
            case 'D':
                doubleDown(playerIndex,handIndex);
                return; // player bust checked inside double down, and even if not bust the play ends here
            case 'H':
                players[playerIndex].cards[handIndex].push_back(getCard());
                playerBust = checkPlayerBust(playerIndex,handIndex);
                if (playerBust)
                    return;
                break;
            default:
                break;
        }
    }
}

void Table::split(unsigned playerIndex, unsigned handIndex)
{
    // money for new cards, has to be same size as pot    
    unsigned money = players[playerIndex].player->getMoney(players[playerIndex].pot[handIndex]);
    // put money in the newPot
    vector <unsigned>::iterator it_pot = players[playerIndex].pot.begin();
    players[playerIndex].pot.insert(it_pot+handIndex+1,money);
    // create new hand with the second card of first hand
    vector <unsigned short> newHand;
    // put second card of first hand in the newHand
    newHand.push_back(players[playerIndex].cards[handIndex][1]);
    // remove card, since there are two cards, pop_back removes [1]
    players[playerIndex].cards[handIndex].pop_back();
    // add newHand to hands
    vector <vector <unsigned short> >::iterator it_cards = players[playerIndex].cards.begin();
    players[playerIndex].cards.insert(it_cards+handIndex+1,newHand);
    
    // give a card to the two new hands
    players[playerIndex].cards[handIndex].push_back(getCard());
    players[playerIndex].cards[handIndex+1].push_back(getCard());
}    

void Table::doubleDown(unsigned playerIndex, unsigned handIndex)
{
    // double the money, so player has to put what is in the pot
    unsigned money = players[playerIndex].player->getMoney(players[playerIndex].pot[handIndex]);
    players[playerIndex].pot[handIndex] += money; 
    // give card
    players[playerIndex].cards[handIndex].push_back(getCard());
    // check if player bust    
    checkPlayerBust(playerIndex);
}

bool Table::checkPlayerBust(unsigned playerIndex, unsigned handIndex)
{   // hand index choses on which hand to calculate the value (there can be more hands if split)
    if (handValue(playerIndex,handIndex) > 21)
    {   //bust
        /*** empty cards ***/
        while (players[playerIndex].cards[handIndex].size() > 0) 
        {
            players[playerIndex].cards[handIndex].pop_back();
        }
        /*******************/
        // remove money from pot
        players[playerIndex].pot[handIndex] = 0;
        return true;
    }
    return false;
}

unsigned Table::handValue(unsigned playerIndex, unsigned handIndex)
{   // hand index choses on which hand to calculate the value (there can be more hands if split)
    unsigned handValue = 0;
    for (unsigned i = 0; i < players[playerIndex].cards[handIndex].size(); i++)
    {
        handValue += players[playerIndex].cards[handIndex][i];
    }
    return handValue;
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

