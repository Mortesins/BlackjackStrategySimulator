#include "Table.hpp"

#include <iostream>

double testHand(unsigned NumberOfSimulations, unsigned short dealerUpCard, unsigned short playerCard1, unsigned short playerCard2, bool print=false)
{   // returns profit, percent from starting budget
    unsigned money = 0;
    double gain;

    Table t(print, 6); // Print=true,6 decks, cardsToRemove=tmp

    for (unsigned i = 0; i < NumberOfSimulations; i++)
    {
        std::cout << "\t\t\tNumber: " << i << std::endl;
        money += t.playHandTest(dealerUpCard, playerCard1, playerCard2);
    }
    gain = (money / (float)NumberOfSimulations - 20) / 20.0;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "Average money: " << money / (float)NumberOfSimulations <<" starting from 20"<< std::endl;
    return gain;
}

int main()
{
/********** SHOE TEST *******************/
    //Shoe s = Shoe(1,0.7);
    //for (unsigned i = 0; i < 36; i++)
        //std::cout << s.getCard() << std::endl;
    //std::cout << "Decks remaining: " << s.decksRemaining() << std::endl;
    //std::cout << "Is finished: " << s.isFinished() << std::endl;
    //std::cout << s.getCard() << std::endl;
    //std::cout << "Decks remaining: " << s.decksRemaining() << std::endl;
    //std::cout << "Is finished: " << s.isFinished() << std::endl;
    //s.shuffle();
    //std::cout << "Decks remaining: " << s.decksRemaining() << std::endl;
/****************************************/
/*********** PRINT TEST ***********/
    //std::vector< std::vector<unsigned short> > c;
    //std::vector<unsigned short> tmp;
    //c.push_back(tmp);
    //c[0].push_back(1);
    //c[0].push_back(9);
    //c.push_back(tmp);
    //c[1].push_back(7);
    //c[1].push_back(7);
    //Player p(c,"gigi");
    //PlayerSeat ps(&p);
    //ps.pot.push_back(10);
    //ps.pot.push_back(10);
    //std::cout << ps << std::endl;
    //Table t(ps);
    //Dealer* dealer = t.dddd();
    //dealer->newCard(1);
    //t.printDealerUpCardAndCardsRemaining();
    //t.dealerPlay();
    //t.printDealerAndCardsRemaining();
/**********************************/

    testHand(1000,1,1,1, true);

    return 0;
}
