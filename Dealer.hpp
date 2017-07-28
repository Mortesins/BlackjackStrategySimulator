#ifndef DEALER_HPP
#define DEALER_HPP

#include <vector>

using namespace std;

class Dealer
{
  private:
    vector <unsigned short> cards;
    unsigned short hand;
    bool softhit;
    bool soft;

  public:
    Dealer(bool softhit);
    unsigned short getHand();
    unsigned short upCard();
    bool hit();
    void newCard(unsigned short c);
    bool blackjack();
};

#endif
