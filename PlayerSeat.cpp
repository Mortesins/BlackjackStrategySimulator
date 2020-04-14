#include "PlayerSeat.hpp"

PlayerSeat::PlayerSeat()
{
    player = new Player("gigi",this);
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
    {
        ++streak;
    }
    else // streak < 0
    {
        streak = 1; // so I know I won 1 hand
    }
}

void PlayerSeat::updateStreakLose()
{
    if (streak <= 0)
    {
        --streak;
    }
    else // streak > 0
    {
        streak = -1; // so I know I lost 1 hand
    }
}

ostream& operator<<(ostream& os, const PlayerSeat& ps)
{
    os << "Player Seat:" << std::endl;
    os << *(ps.player);
    os << "\tPots:\t";
    unsigned i = 0;
    if (ps.pot.size() != 0)
    {
        while (i < ps.pot.size() - 1)
        {
            os << ps.pot[i] << "\t\t";
            i++;
        }
        os << ps.pot[i] << std::endl;
    }
    return os;
}
/*** TEST const std::vector< std::vector<unsigned short> > & ***/
/*int main()
{
    // TEST const std::vector< std::vector<unsigned short> > & //
    PlayerSeat ps;
    std::vector<unsigned short> tmp;
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
