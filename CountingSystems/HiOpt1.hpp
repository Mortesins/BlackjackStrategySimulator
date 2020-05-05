#ifndef HI_OPT_1_HPP
#define HI_OPT_1_HPP

#include "../CountingSystem.hpp"

class HiOpt1
  : public CountingSystem
{
  public:
    virtual ~HiOpt1() {};
    virtual int cardValue(unsigned short card) const;
};

#endif
