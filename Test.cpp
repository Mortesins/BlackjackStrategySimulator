#include "Table.hpp"

#include <iostream>

using namespace std;

double testHand(unsigned NumberOfSimulations, unsigned short dealerUpCard, unsigned short playerCard1, unsigned short playerCard2, bool print=false)
{   // returns profit, percent from starting budget
    unsigned money = 0;
    double gain;
    
    Table t(print,6); // Print=true,6 decks, cardsToRemove=tmp
    
    for (unsigned i = 0; i < NumberOfSimulations; i++)
    {
        cout << "\t\t\tNumber: " << i << endl;
        money += t.playHandTest(dealerUpCard,playerCard1,playerCard2);
    }
    gain = (money / (float)NumberOfSimulations - 20) / 20.0;
    cout << endl;
    cout << endl;
    cout << "Average money: " << money / (float)NumberOfSimulations <<" starting from 20"<< endl;
    return gain;
}

int main()
{
/********** SHOE TEST *******************/
    //Shoe s = Shoe(1,0.7);
    //for (unsigned i = 0; i < 36; i++)
        //cout << s.getCard() << endl;
    //cout << "Decks remaining: " << s.decksRemaining() << endl;
    //cout << "Is finished: " << s.isFinished() << endl;
    //cout << s.getCard() << endl;
    //cout << "Decks remaining: " << s.decksRemaining() << endl;
    //cout << "Is finished: " << s.isFinished() << endl;
    //s.shuffle();
    //cout << "Decks remaining: " << s.decksRemaining() << endl;
/****************************************/
/*********** PRINT TEST ***********/
    //vector < vector <unsigned short> > c;
    //vector <unsigned short> tmp;
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
    //cout << ps << endl;
    //Table t(ps);
    //Dealer* dealer = t.dddd();
    //dealer->newCard(1);
    //t.printDealerUpCardAndCardsRemaining();
    //t.dealerPlay();
    //t.printDealerAndCardsRemaining();
/**********************************/
    
    testHand(1000,1,1,1);

    return 0;
}
