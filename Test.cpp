#include "Table.hpp"
#include "Player.hpp"
#include "Constants.hpp"
#include "Strategy/StrategyMultiplier.hpp"

int main(int argc, char** argv)
{
    StrategyMultiplier s;
    Player player("gigi", 20*MINIMUM_BET, s);
    Table t({&player}, 6, true);
    while (t.playRound())
    {}
    return 0;
}
