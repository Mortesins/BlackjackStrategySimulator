#include "Table.hpp"

#include <iostream>

using namespace std;

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
    vector < vector <unsigned short> > c;
    vector <unsigned short> tmp;
    c.push_back(tmp);
    c[0].push_back(1);
    c[0].push_back(9);
    c.push_back(tmp);
    c[0].push_back(7);
    c[0].push_back(7);
    c[1].push_back(7);
    Player p(c,"gigi");
    cout << p << endl;
    PlayerSeat ps(&p);
    ps.pot.push_back(10);
    ps.pot.push_back(10);
    ps.pot.push_back(10);
    cout << ps << endl;
    Table t(ps);
    Dealer* dealer = t.dddd();
    dealer->newCard(1);
    t.printDealerUpCardAndCardsRemaining();
    return 0;
}
