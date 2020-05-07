#ifndef ACTION_HPP
#define ACTION_HPP

#include <iostream>

enum class Action
{
    HIT,
    STAND,
    SPLIT,
    DOUBLEDOWN,
    SURRENDER
};

std::ostream& operator<<(std::ostream& os, const Action& action);

namespace action
{
    Action fromChar(char c);
    char toChar(Action a);
}

#endif
