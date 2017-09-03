#ifndef TABLE_HPP
#define TABLE_HPP

using namespace std;

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
    vector <PlayerSeat*> players;
    Dealer dealer;
    Shoe shoe;
    Rules* rules;
    CountingSystem* countingSystem;
    int runningCount;
    unsigned betSize;
    bool americanDealer;
    
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
    Table(PlayerSeat* ps);
    
    void playRound();
    void printDealerAndCardsRemaining();
    void printDealerUpCardAndCardsRemaining();
    void printPlayerSeats();
    
};

#endif
