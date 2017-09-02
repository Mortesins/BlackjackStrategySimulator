#include "Table.hpp"

Table::Table()
    : dealer(false),shoe(6,0.3)
{
   players.push_back(PlayerSeat());
   rules = new Rules();
   countingSystem = new CountingSystem();
}

Table::Table(PlayerSeat& ps)
    : dealer(false),shoe(6,0.3)
{
   players.push_back(ps);
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
        bet = players[i].player->getBet(trueCount,players[i].streak);
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

void Table::insurance()
{
    double tc = trueCount();
    unsigned bet;
    for (unsigned i = 0; i < players.size(); i++)
    {
        bet = players[i].pot[0];
        players[i].insurance = players[i].player->getInsurance(tc,bet); //if no insurance it will be 0
    }
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
        tc = trueCount();
        // call getPlay (should give actionsAllowed here based on Rules)
        play = players[playerIndex].player->getPlay(tc,dealerUpCard,handIndex);
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
    unsigned money = players[playerIndex].player->payMoney(players[playerIndex].pot[handIndex]);
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
    unsigned money = players[playerIndex].player->payMoney(players[playerIndex].pot[handIndex]);
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

void Table::dealerPlay()
{
    if (americanDealer) // add hole card to running count
    {
        runningCount += countingSystem->cardValue(dealer.holeCard());
    }
    while (dealer.hit())
    {
        dealer.newCard(getCard());
    }
}

void Table::giveCollectMoney()
{
    unsigned sum;
    unsigned dealerHand = dealer.getHand();
    // if dealer bust
    if (dealerHand > 21)
    {    // pay everyone
        for (unsigned i = 0; i < players.size(); i++)
        {
            sum = 0;
            // sum all pots
            for (unsigned j = 0; j < players[i].pot.size(); j++)
            {
                sum += players[i].pot[j]; //if player bust pot = 0
            }
            // reset all pots
            while (players[i].pot.size() > 0) 
            {
                players[i].pot.pop_back();
            }
            // give the sum*2 to the player
            players[i].player->receiveMoney(sum*2);
            // player won
            players[i].updateStreakWin();
        }
    }
    else
    { // else
        for (unsigned playerIndex = 0; playerIndex < players.size(); playerIndex++)
        {   // for each player
            for (unsigned handIndex = 0; handIndex < players[playerIndex].cards.size(); handIndex++)
            {   // for each hand
                // if blackjack
                if (blackjack(playerIndex,handIndex))
                {
                    // pay player 3:2, NOTE: BJ vs BJ already taken care
                    players[playerIndex].player->receiveMoney( (unsigned)(players[playerIndex].pot[handIndex]*2.5) );
                    // remove pot money
                    players[playerIndex].pot.erase(players[playerIndex].pot.begin()+handIndex);
                    // player won
                    players[playerIndex].updateStreakWin();
                }
                else
                {    // else
                    // if handValue > dealerHand
                    if (handValue(playerIndex,handIndex) > dealerHand)
                    {
                        // pay player
                        players[playerIndex].player->receiveMoney(players[playerIndex].pot[handIndex]*2);
                        // player won
                        players[playerIndex].updateStreakWin();
                    }
                    else if (handValue(playerIndex,handIndex) == dealerHand)
                    {   // else if handValue == dealerHand
                        // give back money
                        players[playerIndex].player->receiveMoney(players[playerIndex].pot[handIndex]);
                        // streak remain the same
                    }
                    else
                    {   // handValue < dealerHand
                        // player lost NOTE: having two hands and losing with both counts as 2 losses
                        players[playerIndex].updateStreakLose();
                    }
                    // remove money from pot, either because lost but even reset after win
                    players[playerIndex].pot.erase(players[playerIndex].pot.begin()+handIndex);
                }
            }
        }
    }
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

unsigned Table::handValue(unsigned playerIndex, unsigned handIndex)
{   // hand index choses on which hand to calculate the value (there can be more hands if split)
    unsigned handValue = 0;
    for (unsigned i = 0; i < players[playerIndex].cards[handIndex].size(); i++)
    {
        handValue += players[playerIndex].cards[handIndex][i];
    }
    return handValue;
}

bool Table::blackjack(unsigned playerIndex, unsigned handIndex)
{   // only possibility is [1,10] or [10,1]
    return ( 
              (  (players[playerIndex].cards[handIndex][0] == 1) && (players[playerIndex].cards[handIndex][1] == 10)  ) || 
              (  (players[playerIndex].cards[handIndex][0] == 10) && (players[playerIndex].cards[handIndex][1] == 1)  )
           );
}

void Table::checkDealerBlackjack()
{
    if (dealer.blackjack())
    {
        for (unsigned i = 0; i < players.size(); i++)
        {
            // check if player has hand with blackjack
            for (unsigned j = 0; j < players[i].cards.size(); j++)
            {
                if (blackjack(i,j))
                {   // draw, give back pot money. NOTE: Rules should check if BJvsBJ is a draw
                    players[i].player->receiveMoney(players[i].pot[j]);
                    // remove pot money
                    players[i].pot.erase(players[i].pot.begin()+j);
                    // draw so streak remains the same
                }
                else
                {   // no blackjack so player lost. NOTE: having two hands and losing with both counts as 2 losses
                    players[i].updateStreakLose();
                }
            }
            // remove all remaining (no blackjack) bets of all pots (there are more pots if split)
            while (players[i].pot.size() > 0) 
            {
                players[i].pot.pop_back();
            }
            // payout insurance, note if player no insurance then 0*3 = 0
            players[i].player->receiveMoney(players[i].insurance*3);
            // remove insurance
            players[i].insurance = 0;
        }
    }
    else
    {
        //remove insurance
        for (unsigned i = 0; i < players.size(); i++)
        {
            players[i].insurance = 0;
        }
    }
}

void Table::playRound()
{
    if (playersInPlay())
    {
        placeBets();
        distributeCards();
        insurance();
        if (americanDealer)
            checkDealerBlackjack();
        playersPlay();
        dealerPlay();
        if (!americanDealer)
            checkDealerBlackjack();
        giveCollectMoney();
    }
    else
    {
        // no players are playing
        return;
    }
}

void Table::printDealerUpCardAndCardsRemaining()
{
    unsigned short upCard = dealer.upCard();
    if (upCard == 1)
        cout << "Dealer:\tA" << endl;
    else
        cout << "Dealer:\t" << upCard << endl;
    cout << "Cards remaining: "  << shoe.cardsRemaining() << endl;
}

void Table::printDealerAndCardsRemaining()
{
    cout << dealer;
    cout << "Cards remaining: "  << shoe.cardsRemaining() << endl;
}
    

