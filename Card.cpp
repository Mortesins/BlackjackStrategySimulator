#include "Card.hpp"
#include "Exceptions.hpp"

namespace card
{
    unsigned short fromString(const std::string& s)
    {
        if (s.size() == 1)
        {
            if (s[0] == 'A')
            {
                return 1;
            }
            unsigned short card = s[0] - '0';
            if (card >= 2 && card <= 9)
            {
                return card;
            }
        }
        else if (s == "10")
        {
            return 10;
        }
        throw ActionConversionError("Cannot convert " + s + " to a valid card. Must be A or 2 through 9.");
    }

    std::string toString(unsigned short card)
    {
        if (card == 1)
        {
            return "A";
        }
        else if (card >= 2 && card <= 10)
        {
            return std::to_string(card);
        }
        throw ActionConversionError(std::string("Unknown card ") + char(card) + ". Cannot convert to char.");
    }
}