#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>
#include <string>
// for ostream
#include <iostream>

#include "Action.hpp"
#include "Strategy/Strategy.hpp"

class PlayerSeat;

class Player
{
    friend ostream& operator<<(ostream& os,const Player& p);
  private:
    const std::string name;
    PlayerSeat* playerSeat;
    unsigned money;
    Strategy& strategy;
  public:
    Player(string n, unsigned money, Strategy& s);

    void assignPlayerSeat(PlayerSeat* ps);

    unsigned getBet(double trueCount, int streak) const;
    Action getPlay(
        double trueCount,
        unsigned short dealerUpCard,
        unsigned handIndex,
        std::vector<Action>& actionsNotAllowed
    ) const;
    unsigned getInsurance(double trueCount, unsigned bet) const;
    unsigned payMoney(unsigned m);
    void receiveMoney(unsigned m);
    void resetMoney(unsigned m);
    unsigned getMoney() const;
};

#endif
