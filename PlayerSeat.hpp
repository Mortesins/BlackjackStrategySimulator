#ifndef PLAYER_SEAT_HPP
#define PLAYER_SEAT_HPP

#include "Player.hpp"
#include <vector>
#include <iostream>

class PlayerSeat
{
  public:
    unsigned insurance;
    int streak; // Wins > 0, Losses < 0
    std::vector<unsigned> pot;
    std::vector<std::vector<unsigned short>> cards;
    Player* const player;

    PlayerSeat(Player* const p);
    void updateStreakWin();
    void updateStreakLose();
};

std::ostream& operator<<(std::ostream& os, const PlayerSeat& ps);
#endif
