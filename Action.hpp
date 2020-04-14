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

#endif
