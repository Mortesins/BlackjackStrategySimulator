#include "Table.hpp"
#include "CountingSystems/HiOpt1.hpp"

Table::Table()
    : dealer(false),shoe(6,0.3),americanDealer(false)
{
   players.push_back(new PlayerSeat());
   rules = new Rules();
   countingSystem = new HiOpt1();
   runningCount = 0;
   print = false;
}

Table::Table(bool p)
    : dealer(false),shoe(6,0.3),americanDealer(false)
{
   players.push_back(new PlayerSeat());
   rules = new Rules();
   countingSystem = new HiOpt1();
   runningCount = 0;
   print = p;
}

Table::Table(bool p, unsigned numberOfDecks)
    : dealer(false),shoe(numberOfDecks,0.3),americanDealer(false)
{
   players.push_back(new PlayerSeat());
   rules = new Rules();
   countingSystem = new HiOpt1();
   runningCount = 0;
   print = p;
}

Table::Table(bool p, unsigned numberOfDecks, const std::vector<unsigned short>& cardsToRemove)
    : dealer(false),shoe(numberOfDecks,cardsToRemove),americanDealer(false)
{
   players.push_back(new PlayerSeat());
   rules = new Rules();
   countingSystem = new HiOpt1();
   runningCount = 0;
   print = p;
}

bool Table::playersInPlay()
{
    bool inPlay = false;
    unsigned i = 0;
    while ( !inPlay && (i < players.size()) )
    {
        inPlay = players[i]->player->inPlay();
        ++i;
    }
    return inPlay;
}

void Table::placeBets()
{
    double trueCount = this->trueCount();
    unsigned bet;
    for (unsigned i = 0; i < players.size(); i++)
    {
        bet = players[i]->player->getBet(trueCount,players[i]->streak);
        if (isMultipleOfBetSize(bet))
        {
            players[i]->player->payMoney(bet);
            players[i]->pot.push_back(bet);
        }
        else
        {
            std::cout << "Table::placeBet: bet not multiple of betSize";
            //throw "Table::placeBet: bet not multiple of betSize";
        }
    }
}

void Table::distributeCards()
{
    // cards is std::vector< std::vector<unsigned short> >, at the end of the round is emptied
        // so I need to add an empty "std::vector<unsigned short>" to which i will give the cards
    /*** add empty std::vector and give first card ***/
    std::vector<unsigned short> tmp;
    for (unsigned i = 0; i < players.size(); i++)
    {
        players[i]->cards.push_back(tmp);
        players[i]->cards[0].push_back(getCard());
    }
    /********************************************/

    // give card to dealer
    dealer.newCard(getCard());

    /*** give second card ***/
    for (unsigned i = 0; i < players.size(); i++)
    {
        players[i]->cards[0].push_back(getCard());
    }
    /************************/

    // give second hole card to american dealer without counting it
    if (americanDealer)
    {
        dealer.newCard(getCard(false));
    }
}

void Table::insurance()
{
    double tc = trueCount();
    unsigned bet;
    for (unsigned i = 0; i < players.size(); i++)
    {
        bet = players[i]->pot[0];
        players[i]->insurance = players[i]->player->getInsurance(tc,bet); //if no insurance it will be 0
    }
}

void Table::playersPlay()
{
    for (unsigned i = 0; i < players.size(); i++)
    {
        for (unsigned handIndex = 0; handIndex < players[i]->cards.size(); handIndex++)
        {   // for each hand, NOTE: cards.size() should be changed by playerPlay when split
            playerPlay(i,handIndex);
        }
    }
}

void Table::playerPlay(unsigned playerIndex, unsigned handIndex)
{   // plays handIndex, if split continues to play the first hand of the split, which has same handIndex
    unsigned short dealerUpCard = dealer.upCard();
    std::vector<Action> actionsNotAllowed;
    bool playerBust;
    double tc;

    //std::cout << "\t\t\t\tPlayerPlay " << handIndex << std::endl;

    Action play;
    while (play != Action::STAND) // until player stands
    {
        tc = trueCount();
        // get actions not allowed
        actionsNotAllowed = rules->getActionsNotAllowed(players[playerIndex]->cards, handIndex);
        // call getPlay (should give actionsAllowed here based on Rules)
        play = players[playerIndex]->player->getPlay(tc,dealerUpCard,handIndex,actionsNotAllowed);
        if (print)
        {
            std::cout << "Play: " << play << std::endl;
        }
        switch(play)
        {
            /*** needs implementation
            case 'R':
                // needs implementation
                break;
            ***/
            case Action::SPLIT:
                split(playerIndex,handIndex);
                break; // continues play on the same handIndex
            case Action::DOUBLEDOWN:
                doubleDown(playerIndex,handIndex);
                if (print)
                    printPlayerSeats();
                return; // player bust checked inside double down, and even if not bust the play ends here
            case Action::HIT:
                players[playerIndex]->cards[handIndex].push_back(getCard());
                playerBust = checkPlayerBust(playerIndex,handIndex);
                if (playerBust)
                {
                    if (print)
                    {
                        std::cout << "\\********* Player Bust ************/" << std::endl;
                        printPlayerSeats();
                    }
                    return;
                }
                break;
            default:
                break;
        }

        if (print)
        {
            printPlayerSeats();
        }
    }
}

void Table::split(unsigned playerIndex, unsigned handIndex)
{
    // money for new cards, has to be same size as pot
    unsigned money = players[playerIndex]->player->payMoney(players[playerIndex]->pot[handIndex]);
    // put money in the newPot
    std::vector<unsigned>::iterator it_pot = players[playerIndex]->pot.begin();
    players[playerIndex]->pot.insert(it_pot+handIndex+1,money);
    // create new hand with the second card of first hand
    std::vector<unsigned short> newHand;
    // put second card of first hand in the newHand
    newHand.push_back(players[playerIndex]->cards[handIndex][1]);
    // remove card, since there are two cards, pop_back removes [1]
    players[playerIndex]->cards[handIndex].pop_back();
    // add newHand to hands
    std::vector<std::vector<unsigned short> >::iterator it_cards = players[playerIndex]->cards.begin();
    players[playerIndex]->cards.insert(it_cards+handIndex+1,newHand);

    // give a card to the two new hands
    players[playerIndex]->cards[handIndex].push_back(getCard());
    players[playerIndex]->cards[handIndex+1].push_back(getCard());
}

void Table::doubleDown(unsigned playerIndex, unsigned handIndex)
{
    // double the money, so player has to put what is in the pot
    unsigned money = players[playerIndex]->player->payMoney(players[playerIndex]->pot[handIndex]);
    players[playerIndex]->pot[handIndex] += money;
    // give card
    players[playerIndex]->cards[handIndex].push_back(getCard());
    // check if player bust
    checkPlayerBust(playerIndex);
}

bool Table::checkPlayerBust(unsigned playerIndex, unsigned handIndex)
{   // hand index choses on which hand to calculate the value (there can be more hands if split)
    if (handValue(playerIndex,handIndex) > 21)
    {   //bust
        if (print)
        {
            std::cout << "/********* Player Bust ************/" << std::endl;
            printPlayerSeats();
        }
        /*** empty cards ***/
        players[playerIndex]->cards[handIndex].clear();
        /*******************/
        // remove money from pot
        players[playerIndex]->pot[handIndex] = 0;
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
    //std::cout << "GiveCollectMoney" << std::endl;
    unsigned sum;
    unsigned dealerHand = dealer.getHand();
    // if dealer bust
    if (dealerHand > 21)
    {    // pay everyone
        for (unsigned playerIndex = 0; playerIndex < players.size(); playerIndex++)
        {
            sum = 0;
            // sum all pots
            for (unsigned handIndex = 0; handIndex < players[playerIndex]->pot.size(); handIndex++)
            {
                if (blackjack(playerIndex,handIndex))
                {
                    players[playerIndex]->player->receiveMoney( (unsigned)(players[playerIndex]->pot[handIndex]*2.5) );
                }
                else
                {
                    sum += players[playerIndex]->pot[handIndex]; //if player bust pot = 0
                }
                players[playerIndex]->pot[handIndex] = 0; // reset all pot
            }
            // give the sum*2 to the player
            players[playerIndex]->player->receiveMoney(sum*2);
            // player won
            players[playerIndex]->updateStreakWin();
        }
    }
    else
    { // else
        for (unsigned playerIndex = 0; playerIndex < players.size(); playerIndex++)
        {   // for each player
            for (unsigned handIndex = 0; handIndex < players[playerIndex]->cards.size(); handIndex++)
            {   // for each hand
                // if blackjack
                if (blackjack(playerIndex,handIndex))
                {
                    // pay player 3:2, NOTE: BJ vs BJ already taken care
                    players[playerIndex]->player->receiveMoney( (unsigned)(players[playerIndex]->pot[handIndex]*2.5) );
                    // remove pot money
                    players[playerIndex]->pot[handIndex] = 0;
                    // player won
                    players[playerIndex]->updateStreakWin();
                }
                else
                {    // else
                    // if handValue > dealerHand
                    if (handValue(playerIndex,handIndex) > dealerHand)
                    {
                        // pay player
                        players[playerIndex]->player->receiveMoney(players[playerIndex]->pot[handIndex]*2);
                        // player won
                        players[playerIndex]->updateStreakWin();
                    }
                    else if (handValue(playerIndex,handIndex) == dealerHand)
                    {   // else if handValue == dealerHand
                        // give back money
                        players[playerIndex]->player->receiveMoney(players[playerIndex]->pot[handIndex]);
                        // streak remain the same
                    }
                    else
                    {   // handValue < dealerHand
                        // player lost NOTE: having two hands and losing with both counts as 2 losses
                        players[playerIndex]->updateStreakLose();
                    }
                    // remove money from pot, either because lost but even reset after win
                    players[playerIndex]->pot[handIndex] = 0;
                }
            }
        }
    }
}

void Table::trashCardsAndEmptyPots()
{
    dealer.reset();
    for (unsigned i = 0; i < players.size(); i++)
    {
        players[i]->cards.clear();
        players[i]->pot.clear();
    }
}

double Table::trueCount()
{
    return runningCount / shoe.decksRemaining();
}

bool Table::isMultipleOfBetSize(unsigned bet)
{
    return ( (bet % 2) == 0 );
}

unsigned short Table::getCard(bool countCard)
{ // no counting when giving second hole card to american dealer
    unsigned short card = shoe.getCard();
    if (countCard)
    {
        runningCount += countingSystem->cardValue(card);
    }
    return card;
}

unsigned Table::handValue(unsigned playerIndex, unsigned handIndex)
{   // hand index choses on which hand to calculate the value (there can be more hands if split)
    unsigned handValue = 0;
    if (players[playerIndex]->cards[handIndex].empty())
    {
        return handValue; // zero
    }
    for (unsigned i = 0; i < players[playerIndex]->cards[handIndex].size(); i++)
    {
        handValue += players[playerIndex]->cards[handIndex][i];
    }
    return handValue;
}

bool Table::blackjack(unsigned playerIndex, unsigned handIndex)
{   // only possibility is [1,10] or [10,1]
    if (players[playerIndex]->cards[handIndex].empty()) // if player bust
        return false;
    return (
      (  (players[playerIndex]->cards[handIndex][0] == 1) && (players[playerIndex]->cards[handIndex][1] == 10)  ) ||
      (  (players[playerIndex]->cards[handIndex][0] == 10) && (players[playerIndex]->cards[handIndex][1] == 1)  )
   );
}

bool Table::checkDealerBlackjack()
{
    //std::cout << "checkDealer Blackjack" << std::endl;
    if (dealer.blackjack())
    {
        for (unsigned i = 0; i < players.size(); i++)
        {
            // check if player has hand with blackjack
            for (unsigned j = 0; j < players[i]->cards.size(); j++)
            {
                if (blackjack(i,j))
                {   // draw, give back pot money. NOTE: Rules check if BJvsBJ is a draw
                    if (rules->blackjackBlackjackPush())
                    {
                        players[i]->player->receiveMoney(players[i]->pot[j]);
                    }
                    // remove pot money
                    players[i]->pot[j] = 0;
                    // draw so streak remains the same
                }
                else
                {   // no blackjack so player lost. NOTE: having two hands and losing with both counts as 2 losses
                    players[i]->updateStreakLose();
                }
            }
            // remove all remaining (no blackjack) bets of all pots (there are more pots if split)
            while (players[i]->pot.size() > 0)
            {
                players[i]->pot.pop_back();
            }
            // payout insurance, note if player no insurance then 0*3 = 0
            players[i]->player->receiveMoney(players[i]->insurance*3);
            // remove insurance
            players[i]->insurance = 0;
        }
        return true;
    }
    else
    {
        //remove insurance
        for (unsigned i = 0; i < players.size(); i++)
        {
            players[i]->insurance = 0;
        }
        return false;
    }
}

void Table::playRound()
{
    placeBets();
    distributeCards();
    insurance();
    if (americanDealer)
    {
        checkDealerBlackjack();
    }
    if (print)
    {
        printDealerUpCardAndCardsRemaining();
        printPlayerSeats();
        std::cout << "/****************************/" << std::endl;
    }
    playersPlay();
    if (print)
    {
        printDealerUpCardAndCardsRemaining();
        std::cout << "/****************************/" << std::endl;
    }
    dealerPlay();
    if (print)
    {
        printDealerAndCardsRemaining();
        printPlayerSeats();
        std::cout << "/****************************/" << std::endl;
    }
    if (!americanDealer)
    {
        if (!checkDealerBlackjack()) // if true blackjack did not happen
        {
            giveCollectMoney();
        }
    }
    else
    {
        giveCollectMoney();
    }
    if (print)
    {
        std::cout << "Player Money: " << players[0]->player->getMoney() << std::endl;
    }
    trashCardsAndEmptyPots();
}

/********************* SINGLE HAND TEST ************************************/
unsigned Table::playHandTest(unsigned short dealerUpCard, unsigned short playerCard1, unsigned short playerCard2)
{   // returns money of player at end of hand
    std::vector<unsigned short> cardsToRemove;
    cardsToRemove.push_back(dealerUpCard);
    cardsToRemove.push_back(playerCard1);
    cardsToRemove.push_back(playerCard2);
    shoe.shuffleAndRemoveCards(cardsToRemove);

    placeBets();
/************************/
    distributeCardsSpecificHand(dealerUpCard,playerCard1,playerCard2);
/************************/
    insurance();
    if (americanDealer)
    {
        checkDealerBlackjack();
    }
    if (print)
    {
        printDealerUpCardAndCardsRemaining();
        printPlayerSeats();
        std::cout << "/****************************/" << std::endl;
    }
    playersPlay();
    if (print)
    {
        printDealerUpCardAndCardsRemaining();
        std::cout << "/****************************/" << std::endl;
    }
    dealerPlay();
    if (print)
    {
        printDealerAndCardsRemaining();
        printPlayerSeats();
        std::cout << "/****************************/" << std::endl;
    }
    if (!americanDealer)
    {
        if (!checkDealerBlackjack()) // if true blackjack did not happen
        {
            giveCollectMoney();
        }
    }
    else
    {
        giveCollectMoney();
    }
    if (print)
    {
        std::cout << "Player Money: " << players[0]->player->getMoney() << std::endl;
    }
    trashCardsAndEmptyPots();
    return players[0]->player->getMoney();
}

void Table::distributeCardsSpecificHand(unsigned short dealerUpCard, unsigned short playerCard1, unsigned short playerCard2)
{
    // cards is std::vector< std::vector<unsigned short> >, at the end of the round is emptied
        // so I need to add an empty "std::vector<unsigned short>" to which i will give the cards
    /*** add empty std::vector and give first card ***/
    std::vector<unsigned short> tmp;
    for (unsigned i = 0; i < players.size(); i++)
    {
        players[i]->cards.push_back(tmp);
        players[i]->cards[0].push_back(playerCard1);
    }
    /********************************************/

    // give card to dealer
    dealer.newCard(dealerUpCard);

    /*** give second card ***/
    for (unsigned i = 0; i < players.size(); i++)
    {
        players[i]->cards[0].push_back(playerCard2);
    }
    /************************/

    // give second hole card to american dealer without counting it
    if (americanDealer)
    {
        dealer.newCard(getCard(false));
    }
}

/********************* TESTING ************************************/
void Table::playRoundTest()
{
    placeBets();
/************************/
    distributeCardsSplit();
/************************/
    insurance();
    if (americanDealer)
    {
        checkDealerBlackjack();
    }
    if (print)
    {
        printDealerUpCardAndCardsRemaining();
        printPlayerSeats();
        std::cout << "/****************************/" << std::endl;
    }
    playersPlay();
    if (print)
    {
        printDealerUpCardAndCardsRemaining();
        std::cout << "/****************************/" << std::endl;
    }
    dealerPlay();
    if (print)
    {
        printDealerAndCardsRemaining();
        printPlayerSeats();
        std::cout << "/****************************/" << std::endl;
    }
    if (!americanDealer)
    {
        if (!checkDealerBlackjack()) // if true blackjack did not happen
        {
            giveCollectMoney();
        }
    }
    else
    {
        giveCollectMoney();
    }
    if (print)
    {
        std::cout << "Player Money: " << players[0]->player->getMoney() << std::endl;
    }
    trashCardsAndEmptyPots();
}

void Table::distributeCardsSplit()
{
    // cards is std::vector< std::vector<unsigned short> >, at the end of the round is emptied
        // so I need to add an empty "std::vector<unsigned short>" to which i will give the cards
    /*** add empty std::vector and give first card ***/
    std::vector<unsigned short> tmp;
    for (unsigned i = 0; i < players.size(); i++)
    {
        players[i]->cards.push_back(tmp);
        players[i]->cards[0].push_back(1);
    }
    /********************************************/

    // give card to dealer
    dealer.newCard(1);

    /*** give second card ***/
    for (unsigned i = 0; i < players.size(); i++)
    {
        players[i]->cards[0].push_back(1);
    }
    /************************/

    // give second hole card to american dealer without counting it
    if (americanDealer)
    {
        dealer.newCard(getCard(false));
    }
}

void Table::distributeCardsDoubleDown()
{
    // cards is std::vector< std::vector<unsigned short> >, at the end of the round is emptied
        // so I need to add an empty "std::vector<unsigned short>" to which i will give the cards
    /*** add empty std::vector and give first card ***/
    std::vector<unsigned short> tmp;
    for (unsigned i = 0; i < players.size(); i++)
    {
        players[i]->cards.push_back(tmp);
        players[i]->cards[0].push_back(1);
    }
    /********************************************/

    // give card to dealer
    dealer.newCard(5);

    /*** give second card ***/
    for (unsigned i = 0; i < players.size(); i++)
    {
        players[i]->cards[0].push_back(2);
    }
    /************************/

    // give second hole card to american dealer without counting it
    if (americanDealer)
    {
        dealer.newCard(getCard(false));
    }
}

void Table::printDealerUpCardAndCardsRemaining()
{
    unsigned short upCard = dealer.upCard();
    if (upCard == 1)
    {
        std::cout << "Dealer:\tA" << std::endl;
    }
    else
    {
        std::cout << "Dealer:\t" << upCard << std::endl;
    }
    std::cout << "Cards remaining: "  << shoe.cardsRemaining() << std::endl;
}

void Table::printDealerAndCardsRemaining()
{
    std::cout << dealer;
    std::cout << "Cards remaining: "  << shoe.cardsRemaining() << std::endl;
}

void Table::printPlayerSeats()
{
    //std::cout << "gigi:" << players[0]->cards[0][0] << "-" << players[0]->cards[0][1] << std::endl;
    for (unsigned i = 0; i < players.size(); i++)
    {
        std::cout << *(players[i]);
    }
}
