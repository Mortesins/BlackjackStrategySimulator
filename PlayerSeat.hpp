#ifndef PLAYER_SEAT_HPP
#define PLAYER_SEAT_HPP

using namespace std;

#include "Player.hpp"
#include <vector>

class PlayerSeat
{
  public:
    unsigned insurance;
    int streak; // Wins > 0, Losses < 0
    vector <unsigned> pot;
    vector <vector <unsigned short> > cards;
    Player* player;
    
    PlayerSeat();
    void updateStreakWin();
    void updateStreakLose();
};

#endif
