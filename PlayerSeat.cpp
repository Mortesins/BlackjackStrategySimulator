#include "PlayerSeat.hpp"

PlayerSeat::PlayerSeat()
{
    player = new Player(cards,"gigi");
    streak = 0;
    insurance = 0;
}

PlayerSeat::PlayerSeat(Player* p)
{
    player = p;
    streak = 0;
    insurance = 0;
}

void PlayerSeat::updateStreakWin()
{
    if (streak >= 0)
        streak++;
    else // streak < 0
        streak = 1; // so I know I won 1 hand
}

void PlayerSeat::updateStreakLose()
{
    if (streak <= 0)
        streak--;
    else // streak > 0
        streak = -1; // so I know I lost 1 hand
}

ostream& operator<<(ostream& os, const PlayerSeat& ps)
{
    os << "Player Seat:" << endl;
    os << *(ps.player);
    os << "\tPots:\t";
    unsigned i = 0;
    while (i < ps.pot.size() - 1)
    {
        os << ps.pot[i] << "\t\t";
        i++;
    }
    os << ps.pot[i] << endl;
    return os;
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
