#ifndef PLAYER_SEAT_HPP
#define PLAYER_SEAT_HPP

using namespace std;

#include "Player.hpp"
#include <vector>

class PlayerSeat
{
  public:
    unsigned insurance;
    vector <unsigned> pot;
    vector <vector <unsigned short> > cards;
    Player* player;
    
    PlayerSeat();
};

#endif
