#ifndef TABLE_HPP
#define TABLE_HPP

#include <vector>

#include "PlayerSeat.hpp"
#include "Shoe.hpp"
#include "Dealer.hpp"
#include "Rules.hpp"
#include "CountingSystem.hpp"
// for printDealerAndCardsRemaining()
#include <iostream>

class Table
{
  private:
    std::vector<PlayerSeat*> players;
    Dealer dealer;
    Shoe shoe;
    Rules* rules;
    CountingSystem* countingSystem;
    int runningCount;
    unsigned betSize;
    const bool americanDealer;

    bool print;

    bool playersInPlay();
    void placeBets();
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
    bool checkPlayerBust(unsigned playerIndex, unsigned handIndex = 0);
    void dealerPlay();
    bool checkDealerBlackjack();
    void giveCollectMoney();
    void trashCardsAndEmptyPots();

    double trueCount();
    bool isMultipleOfBetSize(unsigned bet);
    unsigned short getCard(bool countCard = true);
    unsigned handValue(unsigned playerIndex, unsigned handIndex);
    bool blackjack(unsigned playerIndex, unsigned handIndex);
  public:

    Table();
    Table(bool p);
    Table(bool p, unsigned numberOfDecks);
    Table(bool p, unsigned numberOfDecks, const std::vector<unsigned short> & cardsToRemove);

    void playRound();
/****** TEST CERTAIN HAND *******/
    unsigned playHandTest(unsigned short dealerUpCard, unsigned short playerCard1, unsigned short playerCard2);
    void distributeCardsSpecificHand(unsigned short dealerUpCard, unsigned short playerCard1, unsigned short playerCard2);
/********************************/
/****** TEST ******/
    void playRoundTest();
/******************/
    void printDealerAndCardsRemaining();
    void printDealerUpCardAndCardsRemaining();
    void printPlayerSeats();

};

#endif
