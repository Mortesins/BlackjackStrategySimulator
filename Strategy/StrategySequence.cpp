#include "StrategySequence.hpp"

StrategySequence::StrategySequence()
    : Strategy()
{   // default, so the levels are TC [-2 | 2]
    
    // this constructor is for testing only, there is no purpose in having a default
    
    // bettingStrategies[0] has vector of bets for first level (so for TC < -2)
        // only one bet which is zero (so no play while TC < -2)
    bettingStrategies[0][0] = 0;
    // bettingStrategies[1] has vector of bets for -2 < TC < 2
        // only one bet which is base bet (default 2)
    bettingStrategies[1][0] = 2;
    // bettingStrategies[2] has vector of bets for TC < 2
    bettingStrategies[2][0] = 4;
    bettingStrategies[2][1] = 6;
    bettingStrategies[2][2] = 8;
    bettingStrategies[2][3] = 10;
    bettingStrategies[2][4] = 12;
}

unsigned StrategySequence::getBet(double trueCount, unsigned budget, int streak)
{
    /*** I have to find TC interval ***/
        // i will be TC interval index
    unsigned i = 0;
    bool found = false;
    
    while (!found && i < bettingStrategies.size()) // bettingStrategies.size() is the number of TC intervals (like -2 < TC < 2 or TC > 2)
    {
        if (trueCount > levels[i])
            i++;
        else
            found = true;
    }
    /**********************************/
    
    /*** update levelCounter for this TC interval ***/
    if (levelCounters[i] == 0)
    {   // first time I enter this interval, so I have to reset other levelCounters
        for (unsigned j=0; j < levelCounters.size(); j++)
            levelCounters[j] = 0;
        levelCounters[i] = 1;
    }
    else
    {   // I have to increase levelCounters[i]
        levelCounters[i]++;
    }
    /************************************************/
    
    /*** I have to find correct bet for the TC interval ***/
    // based on how many times I have being in the level, I have to get the correct bet from the vector bettingStrategies[i]
    unsigned betIndex;
    if (levelCounters[i] <= bettingStrategies[i].size())
        betIndex = levelCounters[i] - 1; //because if levelCounters[i] = 1, one time in that interval, so first bet so index 0
    else // example: 5 time in interval, but that interval has 3 bets, so I choose the last bet (third bet)
        betIndex = bettingStrategies[i].size() - 1;
    /******************************************************/
    return this->stopStrategy.canPlaceBet(budget,bettingStrategies[i][betIndex],consecutiveLosses(streak));
}
