#ifndef PLAYER_SEAT_HPP
#define PLAYER_SEAT_HPP

using namespace std;

#include "Player.hpp"
#include <vector>
// for ostream
#include <iostream>

class Player;

class PlayerSeat
{
  public:
    unsigned insurance;
    int streak; // Wins > 0, Losses < 0
    vector <unsigned> pot;
    vector <vector <unsigned short> > cards;
    Player* player;
    
    PlayerSeat();
    PlayerSeat(Player* p);
    void updateStreakWin();
    void updateStreakLose();
};

ostream& operator<<(ostream& os, const PlayerSeat& ps);
#endif
