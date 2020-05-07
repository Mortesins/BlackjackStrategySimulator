#ifndef DUMMY_STRATEGY_HPP
#define DUMMY_STRATEGY_HPP

#include "Strategy.hpp"

/**********************************************************************************************************************
 * DummyStrategy always bets, needed for single hand test
 **********************************************************************************************************************/

class DummyStrategy
    : public Strategy
{
  public:
    DummyStrategy() {};
    virtual ~DummyStrategy() {};
    virtual unsigned getBet(double trueCount, unsigned budget, int streak);
};

#endif
