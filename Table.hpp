#ifndef TABLE_HPP
#define TABLE_HPP

#include <vector>
#include <iostream>

#include "Shoe.hpp"
#include "Dealer.hpp"
#include "PlayerSeat.hpp"

class Rules;
class CountingSystem;
class Player;

class Table
{
  private:
    const bool print;
    const bool americanDealer;
    const CountingSystem* const countingSystem;

    std::vector<PlayerSeat> players;
    Dealer dealer;
    Shoe shoe;
    Rules* rules;
    int runningCount;

    bool placeBets();
    void distributeCards();
/**** TESTING ****/
    void distributeCardsSplit();
    void distributeCardsDoubleDown();
/*****************/
    void insurance();
    void playersPlay();
    void playerPlay(unsigned playerIndex, unsigned handIndex = 0);
    void split(unsigned playerIndex, unsigned handIndex = 0);
    void doubleDown(unsigned playerIndex, unsigned handIndex = 0);
    bool isPlayerBust(PlayerSeat& playerSeat, unsigned handIndex = 0);
    void dealerPlay();
    bool checkDealerBlackjack();
    bool allPlayersHaveBlackjacks();
    void giveCollectMoney();
    void trashCardsAndEmptyPots();
    bool playRoundAfterDistributedCards();

    double trueCount();
    bool isMultipleOfBetSize(unsigned bet);
    unsigned short getCard();
    unsigned short getCardWithoutCounting();
    bool blackjack(const PlayerSeat& playerSeat, unsigned handIndex);
  public:

    Table(const vector<Player*>& players, bool print=false);
    Table(const vector<Player*>& players, unsigned numberOfDecks, bool print);
    virtual ~Table();

    /**
     * Plays round.
     * Returns true if round played and false if no player placed a bet
     */
    bool playRound();
    /**
     * Plays one round from scratch with specified hand
     */
    void playRoundWithSpecificHand(unsigned short dealerUpCard, unsigned short playerCard1, unsigned short playerCard2);
    unsigned playRoundWithSpecificHandAndReturnPlayerBudget(
        unsigned short dealerUpCard,
        unsigned short playerCard1,
        unsigned short playerCard2
    );
/****** TEST CERTAIN HAND *******/
    unsigned playHandTest(unsigned short dealerUpCard, unsigned short playerCard1, unsigned short playerCard2);
    void distributeCardsSpecificHand(unsigned short dealerUpCard, unsigned short playerCard1, unsigned short playerCard2);
/********************************/
/****** TEST ******/
    void playRoundTest();
/******************/
    void printDealerAndCardsRemaining();
    void printDealerUpCardAndCardsRemaining();
    void printDealerUpCardAndCardsRemainingAndTrueCount();
    void printPlayerSeats();

};


unsigned getHandValue(const PlayerSeat& playerSeat, unsigned handIndex);
#endif
