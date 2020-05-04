#include "PlayerSeat.hpp"

PlayerSeat::PlayerSeat()
{
    player = new Player("gigi", this);
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
    if (ps.pot.size() != 0)
    {
        os << "\tPots:\t";
        unsigned i = 0;
        while (i < ps.pot.size() - 1)
        {
            os << ps.pot[i] << "\t\t";
            i++;
        }
        os << ps.pot[i] << std::endl;
    }
    return os;
}
