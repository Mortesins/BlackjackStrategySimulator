#include "HiOpt1.hpp"

int HiOpt1::cardValue(unsigned short card) const
{
    if (card == 10)
    {
        return -1;
    }
    else if ( (card >= 3) && (card <= 6) )
    {
        return 1;
    }
    return 0;
}
