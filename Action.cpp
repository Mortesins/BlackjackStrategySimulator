#include "Action.hpp"


std::ostream& operator<<(std::ostream& os, const Action& action)
{
    char repr;
    switch (action)
    {
        case Action::SURRENDER:
            repr = 'R';
            break;
        case Action::SPLIT:
            repr = 'P';
            break;
        case Action::DOUBLEDOWN:
            repr = 'D';
            break;
        case Action::HIT:
            repr = 'H';
            break;
        case Action::STAND:
            repr = 'S';
            break;
    }
   os << repr;
   return os;
}
