#ifndef TABLE_HPP
#define TABLE_HPP

using namespace std;

#include <vector>

#include "PlayerSeat.hpp"
#include "Shoe.hpp"
#include "Dealer.hpp"
#include "Rules.hpp"

class Table
{
  private:
    vector <PlayerSeat> players;
    Dealer dealer;
    Shoe shoe;
    Rules* rules;
    int runningCount;
    unsigned betSize;
    
    bool playersInPlay();
    void placeBets();
    void distributeCards();
    void playersPlay();
    void playerPlay(unsigned playerIndex);
    void dealerPlay();
    void giveCollectMoney();
    
    double trueCount();
    bool isMultipleOfBetSize(unsigned bet);
  public:
    Table();
    
    void playRound();
    
};

#endif
