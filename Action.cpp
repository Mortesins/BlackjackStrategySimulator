#include "Action.hpp"
#include "Exceptions.hpp"

std::ostream& operator<<(std::ostream& os, const Action& action)
{
   os << action::toChar(action);
   return os;
}

namespace action
{
    char toChar(Action action)
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
        return repr;
    }

    Action fromChar(char c)
    {
        switch (c)
        {
            case 'R':
                return Action::SURRENDER;
            case 'P':
                return Action::SPLIT;
            case 'D':
                return Action::DOUBLEDOWN;
            case 'H':
                return Action::HIT;
            case 'S':
                return Action::STAND;
        }
        throw ActionConversionError("Invalid char for conversion to Action");
    }
}