#ifndef DEALER_HPP
#define DEALER_HPP

#include <vector>

using namespace std;

class Dealer
{
  private:
    vector <unsigned short> cards;
    unsigned short hand;
    bool soft;
    void updateHand();

  public:
    unsigned short getHand();
    unsigned short upCard();
    void play();
    void hit(unsigned short h);
};



#endif
