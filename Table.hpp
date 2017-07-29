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
    
    bool playersInPlay();
    void placeBets();
    void distributeCards();
    void playersPlay();
    void playerPlay(unsigned playerIndex);
    void dealerPlay();
    void giveCollectMoney();
  public:
    Table();
    
    void playRound();
    
};

#endif
