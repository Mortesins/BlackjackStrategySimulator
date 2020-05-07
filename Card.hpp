#ifndef CARD_HPP
#define CARD_HPP

#include <string>

namespace card
{
    unsigned short fromString(const std::string& s);
    std::string toString(unsigned short card);
}

#endif
