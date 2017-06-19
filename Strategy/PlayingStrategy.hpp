#ifndef PLAYING_STRATEGY_HPP
#define PLAYING_STRATEGY_HPP

using namespace std;

#include <vector>
#include <string>

class PlayingStrategy
{
  private:
    vector <vector <char> > table;
  public:
    PlayingStrategy();
    char getPlay(string playerHand, char dealerHand) const;
};

#endif
