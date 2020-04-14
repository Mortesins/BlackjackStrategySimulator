#ifndef STRATEGY_HPP
#define STRATEGY_HPP

using namespace std;

#include <vector>
#include <string>

#include "../Action.hpp"
#include "PlayingStrategy.hpp"
#include "StopStrategy.hpp"

/**********************************************************************************************************************
 * Strategy abstract class is used to calculate:
 *  -what play to do (hit, stand, etc.)
 *  -what bet
 *  -whether or not to insure
 * All decisions made based on the true count.
 * The play is decided based on the playing strategy that can vary with the true count. Stop strategy also needed
 * because the budget might restrict doubling down or splitting.
 * Should be derived to implement the getBet that decides the bet size
 **********************************************************************************************************************/

class Strategy
{
  protected:
    string name;
    std::vector<double> levels;
    std::vector<PlayingStrategy*> playingStrategies;
    StopStrategy stopStrategy;

    unsigned consecutiveLosses(int streak);
  public:
    Strategy();
    bool getInsurance(double trueCount);
    Action getPlay(
        double trueCount,
        const std::vector<unsigned short>& cards,
        unsigned short dealerUpCard,
        std::vector<Action>& actionsNotAllowed,
        unsigned budget,
        unsigned bet
    ) const;
    Action getPlay(
        double trueCount,
        const std::vector<unsigned short>& cards,
        unsigned short dealerUpCard
    ) const;
    virtual unsigned getBet(double trueCount, unsigned budget, int streak) = 0;
};

#endif
