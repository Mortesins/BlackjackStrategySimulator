#ifndef HI_OPT_1_HPP
#define HI_OPT_1_HPP

#include "../CountingSystem.hpp"

class HiOpt1
  : public CountingSystem
{
  public:
    virtual int cardValue(unsigned short card);
};

#endif