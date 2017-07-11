#ifndef SHOE_HPP
#define SHOE_HPP

#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>

using namespace std;

class Shoe
{
  private:
    unsigned short unused;
    unsigned short numberOfDecks;
    vector <unsigned short> cards;

  public:
    Shoe(unsigned short numberOfDecks, double penetration);
    void shuffle();
    unsigned short getCard();
    bool isFinished();
};



#endif