#include "Table.hpp"
#include "CountingSystems/HiOpt1.hpp"
#include "Exceptions.hpp"
#include "Rules.hpp"
#include "CountingSystem.hpp"
#include "Constants.hpp"
#include <sstream>

unsigned getHandValue(const PlayerSeat& playerSeat, unsigned handIndex)
{   // hand index choses on which hand to calculate the value (there can be more hands if split)
    unsigned handValue = 0;
    if (playerSeat.cards[handIndex].empty())
    {
        return handValue; // zero
    }
    bool acePresent = false;
    for (unsigned short card : playerSeat.cards[handIndex])
    {
        if (card == 1)
        {
            acePresent = true;
        }
        handValue += card;
    }
    if (acePresent && handValue <= 11)
    {
        handValue += 10;
    }
    return handValue;
}

Table::Table(const vector<Player*>& players, bool print)
    : Table(players, 6, print)
{}

Table::Table(const vector<Player*>& players, unsigned numberOfDecks, bool print)
    : print(print), americanDealer(false), countingSystem(new HiOpt1()), dealer(false),
        shoe(numberOfDecks, 0.6)
{
    for (Player* player : players)
    {
        this->players.push_back(PlayerSeat(player));
        player->assignPlayerSeat(&(this->players.back()));
    }
    rules = new Rules();
    runningCount = 0;
    shoe.getCard(); // burn first card
}

Table::~Table()
{
    delete rules;
    delete countingSystem;
}

bool Table::placeBets()
{
    bool atLeastOnePlayerBet = false;
    double trueCount = this->trueCount();
    unsigned bet;
    for (unsigned i = 0; i < players.size(); i++)
    {
        bet = players[i].player->getBet(trueCount, players[i].streak);
        if (bet != 0 && (bet % MINIMUM_BET) == 0)
        {
            atLeastOnePlayerBet = true;
            players[i].pot.push_back(players[i].player->payMoney(bet));
        } // otherwise don't place bet
    }
    return atLeastOnePlayerBet;
}

void Table::distributeCards()
{
    distributeCardsSpecificHand(getCard(), getCard(), getCard());
}

inline void Table::distributeCardsSpecificHand(
    unsigned short dealerUpCard,
    unsigned short playerCard1,
    unsigned short playerCard2
)
{
    // cards is std::vector< std::vector<unsigned short> >, at the end of the round is emptied
        // so I need to add an empty "std::vector<unsigned short>" to which i will give the cards
    /*** add empty std::vector and give first card ***/
    std::vector<unsigned short> tmp;
    for (unsigned i = 0; i < players.size(); i++)
    {
        players[i].cards.push_back(tmp);
        players[i].cards[0].push_back(playerCard1);
    }
    /********************************************/

    // give card to dealer
    dealer.newCard(dealerUpCard);

    /*** give second card ***/
    for (unsigned i = 0; i < players.size(); i++)
    {
        players[i].cards[0].push_back(playerCard2);
    }
    /************************/

    // give second hole card to american dealer without counting it
    if (americanDealer)
    {
        dealer.newCard(getCardWithoutCounting());
    }
}

void Table::insurance()
{
    double tc = trueCount();
    unsigned bet;
    for (unsigned i = 0; i < players.size(); ++i)
    {
        bet = players[i].pot[0];
        players[i].insurance = players[i].player->getInsurance(tc, bet); //if no insurance it will be 0
    }
}

void Table::playersPlay()
{
    for (unsigned playerIndex = 0; playerIndex < players.size(); ++playerIndex)
    {
        for (unsigned handIndex = 0; handIndex < players[playerIndex].cards.size(); ++handIndex)
        {   // for each hand, NOTE: cards.size() should be changed by playerPlay when split
            bool continuePlaying = true;
            while (continuePlaying)
            {
                continuePlaying = playerPlay(playerIndex, handIndex, getPlayerPlay(playerIndex, handIndex));
            }
        }
    }
}

void Table::playersPlay(Action firstAction)
{
    for (unsigned playerIndex = 0; playerIndex < players.size(); ++playerIndex)
    {
        // Do the first action on the first hand only
        bool continuePlaying = false; // so if first action stand, then first iteration of for loop will do nothing
        if (firstAction != Action::STAND)
        {
            if (print)
            {
                std::cout << "First hard coded play: " << firstAction << std::endl;
            }
            // need to call getActionsNotAllowed to trigger the no action after A-A split
            rules->getActionsNotAllowed(players[playerIndex].cards, 0);
            continuePlaying = playerPlay(playerIndex, 0, firstAction);
        }
        for (unsigned handIndex = 0; handIndex < players[playerIndex].cards.size(); ++handIndex)
        {   // for each hand, NOTE: cards.size() should be changed by playerPlay when split
            while (continuePlaying)
            {
                continuePlaying = playerPlay(playerIndex, handIndex, getPlayerPlay(playerIndex, handIndex));
            }
        }
    }
}

Action Table::getPlayerPlay(unsigned playerIndex, unsigned handIndex)
{
    unsigned short dealerUpCard = dealer.upCard();
    std::vector<Action> actionsNotAllowed = rules->getActionsNotAllowed(players[playerIndex].cards, handIndex);
    double tc = trueCount();
    Action play = players[playerIndex].player->getPlay(tc, dealerUpCard, handIndex, actionsNotAllowed);
    if (print)
    {
        std::cout << "Play: " << play << std::endl;
    }
    return play;
}

bool Table::playerPlay(unsigned playerIndex, unsigned handIndex, Action play)
{   // plays handIndex, if split continues to play the first hand of the split, which has same handIndex
    switch (play)
    {
        case Action::SPLIT:
            split(playerIndex, handIndex);
            if (print)
            {
                printPlayerSeats();
            }
            return true; // continue playing
        case Action::DOUBLEDOWN:
            doubleDown(playerIndex, handIndex);
            if (print)
            {
                printPlayerSeats();
            }
            return false; // player bust checked inside double down, and even if not bust the play ends here
        case Action::HIT:
            players[playerIndex].cards[handIndex].push_back(getCard());
            if (print)
            {
                printPlayerSeats();
            }
            return !isPlayerBust(players[playerIndex], handIndex);
        case Action::STAND:
            return false;
        default:
            ostringstream os;
            os << "Should not call Table::playerPlay with " << play;
            throw TableError(os.str());
    }
}

void Table::split(unsigned playerIndex, unsigned handIndex)
{
    // money for new cards, has to be same size as pot
    unsigned money = players[playerIndex].player->payMoney(players[playerIndex].pot[handIndex]);
    // put money in the newPot
    std::vector<unsigned>::iterator it_pot = players[playerIndex].pot.begin();
    players[playerIndex].pot.insert(it_pot+handIndex+1, money);
    // create new hand with the second card of first hand
    std::vector<unsigned short> newHand;
    // put second card of first hand in the newHand
    newHand.push_back(players[playerIndex].cards[handIndex][1]);
    // remove card, since there are two cards, pop_back removes [1]
    players[playerIndex].cards[handIndex].pop_back();
    // add newHand to hands
    std::vector<std::vector<unsigned short> >::iterator it_cards = players[playerIndex].cards.begin();
    players[playerIndex].cards.insert(it_cards+handIndex+1, newHand);

    // give a card to the two new hands
    players[playerIndex].cards[handIndex].push_back(getCard());
    players[playerIndex].cards[handIndex+1].push_back(getCard());
}

void Table::doubleDown(unsigned playerIndex, unsigned handIndex)
{
    // double the money, so player has to put what is in the pot
    unsigned money = players[playerIndex].player->payMoney(players[playerIndex].pot[handIndex]);
    players[playerIndex].pot[handIndex] += money;
    players[playerIndex].cards[handIndex].push_back(getCard());
    isPlayerBust(players[playerIndex]);
}

bool Table::isPlayerBust(PlayerSeat& playerSeat, unsigned handIndex)
{   // hand index chooses on which hand to calculate the value (there can be more hands if split)
    if (getHandValue(playerSeat, handIndex) > 21)
    {   //bust
        if (print)
        {
            std::cout << "/********* Player Bust ********/" << std::endl;
        }
        playerSeat.cards[handIndex].clear();
        playerSeat.pot[handIndex] = 0;
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
        for (PlayerSeat& playerSeat : players)
        {
            sum = 0;
            // sum all pots
            for (unsigned handIndex = 0; handIndex < playerSeat.pot.size(); ++handIndex)
            {
                if (blackjack(playerSeat, handIndex))
                {
                    playerSeat.player->receiveMoney((unsigned)playerSeat.pot[handIndex]*2.5);
                }
                else
                {
                    sum += playerSeat.pot[handIndex]; //if player bust pot = 0
                }
                playerSeat.pot[handIndex] = 0; // reset pot
            }
            // give the sum*2 to the player
            playerSeat.player->receiveMoney(sum*2);
            playerSeat.updateStreakWin();
        }
    }
    else
    {
        unsigned handValue;
        for (PlayerSeat& playerSeat : players)
        {
            for (unsigned handIndex = 0; handIndex < playerSeat.cards.size(); ++handIndex)
            {
                if (blackjack(playerSeat, handIndex))
                {
                    // pay player 3:2, NOTE: BJ vs BJ already taken care
                    playerSeat.player->receiveMoney( (unsigned)(playerSeat.pot[handIndex]*2.5) );
                    playerSeat.pot[handIndex] = 0;
                    playerSeat.updateStreakWin();
                }
                else
                {
                    handValue = getHandValue(playerSeat, handIndex);
                    if (handValue > dealerHand)
                    {
                        playerSeat.player->receiveMoney(playerSeat.pot[handIndex]*2);
                        playerSeat.updateStreakWin();
                    }
                    else if (handValue == dealerHand)
                    {
                        playerSeat.player->receiveMoney(playerSeat.pot[handIndex]);
                        // streak remains the same
                    }
                    else
                    {
                        // player lost NOTE: having two hands and losing with both counts as 2 losses
                        playerSeat.updateStreakLose();
                    }
                    playerSeat.pot[handIndex] = 0; // reset pot
                }
            }
        }
    }
}

void Table::trashCardsAndEmptyPots()
{
    dealer.reset();
    for (PlayerSeat& playerSeat : players)
    {
        playerSeat.cards.clear();
        playerSeat.pot.clear();
    }
}

inline double Table::trueCount()
{
    return runningCount / shoe.decksRemaining();
}

inline unsigned short Table::getCard()
{
    unsigned short card = getCardWithoutCounting();
    runningCount += countingSystem->cardValue(card);
    return card;
}

inline unsigned short Table::getCardWithoutCounting()
{
    return shoe.getCard();
}

bool Table::checkDealerBlackjack()
{
    if (dealer.blackjack())
    {
        for (PlayerSeat& playerSeat : players)
        {
            // check if player has hand with blackjack
            for (unsigned handIndex = 0; handIndex < playerSeat.cards.size(); ++handIndex)
            {
                if (blackjack(playerSeat, handIndex) && rules->blackjackBlackjackPush())
                {   // draw, give back pot money if rules say BJvsBJ is a draw
                    playerSeat.player->receiveMoney(playerSeat.pot[handIndex]);
                    // draw so streak remains the same
                }
                else
                {   // Player lost. NOTE: having two hands and losing with both counts as 2 losses
                    playerSeat.updateStreakLose();
                }
            }
            // remove all cards and pots of player
            playerSeat.cards.clear();
            playerSeat.pot.clear();
            // payout insurance, note if player no insurance then 0*3 = 0
            playerSeat.player->receiveMoney(playerSeat.insurance*3);
            playerSeat.insurance = 0;
        }
        return true;
    }
    else
    {
        for (PlayerSeat& playerSeat : players)
        {
            playerSeat.insurance = 0;
        }
        return false;
    }
}

bool Table::blackjack(const PlayerSeat& playerSeat, unsigned handIndex)
{   // only possibility is [1,10] or [10,1]
    if (playerSeat.cards[handIndex].empty()) // if player bust
        return false;
    return (
      (  (playerSeat.cards[handIndex][0] == 1) && (playerSeat.cards[handIndex][1] == 10)  ) ||
      (  (playerSeat.cards[handIndex][0] == 10) && (playerSeat.cards[handIndex][1] == 1)  )
   );
}

bool Table::allPlayersHaveBlackjacks()
{
    for (const PlayerSeat& player : players)
    {
        for (unsigned handIndex = 0; handIndex < player.cards.size(); ++handIndex)
        {
            if (!blackjack(player, handIndex))
            {
                return false;
            }
        }
    }
    return true;
}

bool Table::playRound()
{
    if (print)
    {
        std::cout << "/******** NEW ROUND *********/" << std::endl;
    }
    bool atLeastOneBetPlaced = checkShoeAndPlaceBets();
    if (!atLeastOneBetPlaced)
    {
        return false;
    }
    distributeCards();
    bool dealerBlackjack = insuranceAndDealerBlackjackIfAmericanDealer();
    if (dealerBlackjack)
    {
        return true;
    }
    playersPlay();
    return dealerPlayAndEndTurn();
}

inline bool Table::checkShoeAndPlaceBets()
{
    if (shoe.isFinished())
    {
        shoe.shuffle();
        shoe.getCard(); // Remove top card
        runningCount = 0;
        if (print)
        {
            std::cout << "Reshuffled deck" << std::endl;
        }
    }
    bool atLeastOneBetPlaced = placeBets();
    if (!atLeastOneBetPlaced && print)
    {
        std::cout << "No bets placed. True Count: "  << trueCount() << std::endl;
    }
    return atLeastOneBetPlaced;
}

inline bool Table::insuranceAndDealerBlackjackIfAmericanDealer()
{
    bool dealerBlackjack = false;
    if (dealer.upCard() == 1)  // ACE
    {
        insurance();
        if (americanDealer)
        {
            dealerBlackjack = checkDealerBlackjack();
        }
    }
    if (print)
    {
        printDealerUpCardAndCardsRemainingAndTrueCount();
        printPlayerSeats();
        std::cout << "/****************************/" << std::endl;
    }
    if (dealerBlackjack && print)
    {
        std::cout << "Dealer blackjack" << std::endl;
        printPlayerSeats();
    }
    return dealerBlackjack;
}

inline bool Table::dealerPlayAndEndTurn()
{
    bool allPlayersHaveBlackjack = allPlayersHaveBlackjacks();
    if (!allPlayersHaveBlackjack || (allPlayersHaveBlackjack && dealer.canMakeBlackjack()))
    {
        dealerPlay();
    }
    if (print)
    {
        std::cout << "/****************************/" << std::endl;
        printDealerAndCardsRemaining();
    }
    bool dealerBlackjack = false;
    if (!americanDealer)
    {
        dealerBlackjack = checkDealerBlackjack();
    }
    if (!dealerBlackjack || americanDealer)  // because if americanDealer and blackjack it would have already terminated
    {
        giveCollectMoney();
    }
    trashCardsAndEmptyPots();
    if (print)
    {
        printPlayerSeats();
    }
    return true;
}

void Table::playRoundWithSpecificHand(
    unsigned short dealerUpCard,
    unsigned short playerCard1,
    unsigned short playerCard2,
    Action firstAction
)
{
    if (print)
    {
        std::cout << "/******** NEW ROUND *********/" << std::endl;
    }
    shoe.shuffleAndRemoveCards({dealerUpCard, playerCard1, playerCard2});
    runningCount = 0;
    placeBets();
    distributeCardsSpecificHand(dealerUpCard, playerCard1, playerCard2);
    bool dealerBlackjack = insuranceAndDealerBlackjackIfAmericanDealer();
    if (dealerBlackjack)
    {
        return;
    }
    playersPlay(firstAction);
    dealerPlayAndEndTurn();
}

unsigned Table::playRoundWithSpecificHandAndReturnPlayerBudget(
    unsigned short dealerUpCard,
    unsigned short playerCard1,
    unsigned short playerCard2,
    Action firstAction
)
{
    playRoundWithSpecificHand(dealerUpCard, playerCard1, playerCard2, firstAction);
    return players[0].player->getMoney();
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
        std::cout << "Player Money: " << players[0].player->getMoney() << std::endl;
    }
    trashCardsAndEmptyPots();
    return players[0].player->getMoney();
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
        std::cout << "Player Money: " << players[0].player->getMoney() << std::endl;
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
        players[i].cards.push_back(tmp);
        players[i].cards[0].push_back(1);
    }
    /********************************************/

    // give card to dealer
    dealer.newCard(1);

    /*** give second card ***/
    for (unsigned i = 0; i < players.size(); i++)
    {
        players[i].cards[0].push_back(1);
    }
    /************************/

    // give second hole card to american dealer without counting it
    if (americanDealer)
    {
        dealer.newCard(getCardWithoutCounting());
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
        players[i].cards.push_back(tmp);
        players[i].cards[0].push_back(1);
    }
    /********************************************/

    // give card to dealer
    dealer.newCard(5);

    /*** give second card ***/
    for (unsigned i = 0; i < players.size(); i++)
    {
        players[i].cards[0].push_back(2);
    }
    /************************/

    // give second hole card to american dealer without counting it
    if (americanDealer)
    {
        dealer.newCard(getCardWithoutCounting());
    }
}

void Table::printDealerUpCardAndCardsRemainingAndTrueCount()
{
    printDealerUpCardAndCardsRemaining();
    std::cout << "True Count: "  << trueCount() << std::endl;
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
    //std::cout << "gigi:" << players[0].cards[0][0] << "-" << players[0].cards[0][1] << std::endl;
    for (unsigned i = 0; i < players.size(); i++)
    {
        std::cout << players[i];
    }
}
