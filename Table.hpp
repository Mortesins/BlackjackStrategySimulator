#ifndef TABLE_HPP
#define TABLE_HPP

using namespace std;

#include <vector>

#include "PlayerSeat.hpp"
#include "Shoe.hpp"
#include "Dealer.hpp"
#include "Rules.hpp"
#include "CountingSystem.hpp"

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
    void playersPlay();
    void playerPlay(unsigned playerIndex);
    void dealerPlay();
    void giveCollectMoney();
    
    double trueCount();
    bool isMultipleOfBetSize(unsigned bet);
    unsigned short getCard(bool countCard = true);
  public:
    Table();
    
    void playRound();
    
};

#endif
