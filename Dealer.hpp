#ifndef DEALER_HPP
#define DEALER_HPP

#include <vector>
// for ostream
#include <iostream>

using namespace std;

class Dealer
{
    friend ostream& operator<<(ostream& os, const Dealer& d);
  private:
    bool softHitFlag;
 
    vector <unsigned short> cards;
    unsigned short hand;
    bool isSoftHand;

  public:
    Dealer(bool softHit);
    unsigned short getHand();
    unsigned short upCard();
    unsigned short holeCard(); //for american dealer
    bool hit();
    void newCard(unsigned short c);
    bool blackjack();
    void reset();
};

#endif
