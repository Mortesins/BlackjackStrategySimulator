#ifndef SHOE_HPP
#define SHOE_HPP

#include <vector>


class Shoe
{
  private:
    unsigned numberOfDecks;
    double penetration;
    std::vector<unsigned short> cards;

  public:
    Shoe(unsigned numberOfDecks, double penetration);
    Shoe(unsigned numberOfDecks, const std::vector<unsigned short>& cardsToRemove);

    void shuffle();
    void shuffleAndRemoveCards(const std::vector<unsigned short>& cardsToRemove);
    void shuffleSpecifiedCards(std::vector<unsigned short> cards);
    unsigned short getCard();
    double decksRemaining();
    unsigned cardsRemaining();
    bool isFinished();

    /******************* TESTING *******************/
    //void printDeck();
};



#endif
