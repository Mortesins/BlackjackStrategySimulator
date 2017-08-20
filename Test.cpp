#include "Table.hpp"

#include <iostream>

using namespace std;

int main()
{
/********** SHOE TEST *******************/
    Shoe s = Shoe(1,0.7);
    for (unsigned i = 0; i < 36; i++)
        cout << s.getCard() << endl;
    cout << "Decks remaining: " << s.decksRemaining() << endl;
    cout << "Is finished: " << s.isFinished() << endl;
    cout << s.getCard() << endl;
    cout << "Decks remaining: " << s.decksRemaining() << endl;
    cout << "Is finished: " << s.isFinished() << endl;
    s.shuffle();
    cout << "Decks remaining: " << s.decksRemaining() << endl;
/****************************************/
    return 0;
}
