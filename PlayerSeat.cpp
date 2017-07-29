#include "PlayerSeat.hpp"

PlayerSeat::PlayerSeat()
{
    player = new Player(cards);
}

/*** TEST const vector < vector <unsigned short> > & ***/
/*int main()
{
    // TEST const vector < vector <unsigned short> > & //
    PlayerSeat ps;
    vector <unsigned short> tmp;
    tmp.push_back(0);
    tmp.push_back(2);
    tmp.push_back(3);
    ps.cards.push_back(tmp);
    tmp.pop_back();
    ps.cards.push_back(tmp);
    ps.player->prova();
    ps.cards[0][0] = 10;
    ps.player->prova();
    /////////////////////////////////////////////////////
    return 0;
}*/
/*******************************************************/
