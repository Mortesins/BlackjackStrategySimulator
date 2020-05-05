#ifndef COUNTING_SYSTEM_HPP
#define COUNTING_SYSTEM_HPP

class CountingSystem
{
  public:
    virtual ~CountingSystem() {};
    virtual int cardValue(unsigned short card) const = 0;
};

#endif
