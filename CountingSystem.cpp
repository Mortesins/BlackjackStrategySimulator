#include "CountingSystem.hpp"

int CountingSystem::cardValue(unsigned short card)
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
