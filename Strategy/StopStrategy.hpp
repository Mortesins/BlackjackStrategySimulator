#ifndef STOP_STRATEGY_HPP
#define STOP_STRATEGY_HPP

/**********************************************************************************************************************
 * StopStrategy decides when to stop playing:
 *  -when budget reached stopAtBudget
 *  -or when consecutive losses more than stopAtNumberOfLosses
 * Based on budget tells whether splitting or doubling is possible
 **********************************************************************************************************************/

class StopStrategy
{
  private:
    unsigned stopAtBudget;
    unsigned stopAtNumberOfLosses;
  public:
    StopStrategy();
    StopStrategy(unsigned stopAtBudget, unsigned stopAtNumberOfLosses);
    StopStrategy(unsigned budget, double percentageOverBudget, unsigned stopAtNumberOfLosses);
    virtual unsigned getBet(unsigned budget, unsigned bet, unsigned consecutiveLosses) const; //returns the bet
    virtual bool canSplit(unsigned budget, unsigned bet) const;
    virtual bool canDouble(unsigned budget, unsigned bet) const;
};

#endif
