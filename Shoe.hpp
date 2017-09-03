#ifndef SHOE_HPP
#define SHOE_HPP

#include <cstdlib>
#include <ctime>
#include <sys/time.h>
#include <vector>
#include <string>

using namespace std;

class Shoe
{
  private:
    unsigned numberOfDecks;
    double penetration;
    vector <unsigned short> cards;

  public:
    Shoe(unsigned numberOfDecks, double penetration);
    Shoe(unsigned numberOfDecks, const vector <unsigned short> & cardsToRemove);
    
    void shuffle();
    void shuffleAndRemoveCards(const vector <unsigned short> & cardsToRemove);
    unsigned short getCard();
    double decksRemaining();
    unsigned cardsRemaining();
    bool isFinished();
    
    /******************* TESTING *******************/
    //void printDeck();
};



#endif
