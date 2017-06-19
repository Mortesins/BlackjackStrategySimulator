#ifndef BETTING_STRATEGY_HPP
#define BETTING_STRATEGY_HPP

using namespace std;

#include <vector>

class BettingStrategy
{
  private:
    vector <unsigned int> bettingSequence;
  public:
    BettingStrategy();
    unsigned int getBet(unsigned int levelCounter) const;
};

#endif
