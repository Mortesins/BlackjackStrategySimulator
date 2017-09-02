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
    vector <PlayerSeat> players;
    Dealer dealer;
    Shoe shoe;
    Rules* rules;
    CountingSystem* countingSystem;
    int runningCount;
    unsigned betSize;
    bool americanDealer;
    
    bool playersInPlay();
    void placeBets();
    void distributeCards();
    void insurance();
    void playersPlay();
    void playerPlay(unsigned playerIndex, unsigned handIndex = 0);
    void split(unsigned playerIndex, unsigned handIndex = 0);
    void doubleDown(unsigned playerIndex, unsigned handIndex = 0);
    bool checkPlayerBust(unsigned playerIndex, unsigned handIndex = 0);
    //void dealerPlay();
    void checkDealerBlackjack();
    void giveCollectMoney();
    void trashCards();
    
    double trueCount();
    bool isMultipleOfBetSize(unsigned bet);
    unsigned short getCard(bool countCard = true);
    unsigned handValue(unsigned playerIndex, unsigned handIndex);
    bool blackjack(unsigned playerIndex, unsigned handIndex);
  public:
            void dealerPlay();
            Dealer* dddd(){ return &dealer; }
  
    Table();
    Table(PlayerSeat& ps);
    
    void playRound();
    void printDealerAndCardsRemaining();
    void printDealerUpCardAndCardsRemaining();
    
};

#endif
