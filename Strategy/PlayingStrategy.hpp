#ifndef PLAYING_STRATEGY_HPP
#define PLAYING_STRATEGY_HPP

using namespace std;

#include <vector>
#include <string>

class PlayingStrategy
{
  private:
    bool hitStand[28][10];
    bool doubleDown[28][10];
    bool split[10][10];
    bool surrender[28][10];
    char orderOfActions[4];
    vector <unsigned short> getCoordinates(const vector <unsigned short>& cards, char dealerHand) const; //returns row and column of table
    void printStrategy() const;
  public:
    PlayingStrategy();
    char getPlay(const vector <unsigned short>& cards, char dealerHand) const;
    char getPlay(const vector <unsigned short>& cards, char dealerHand, vector <char> actionsNotAllowed) const;
};

#endif
