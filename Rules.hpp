#ifndef RULES_HPP
#define RULES_HPP

#include <vector>

#include "Action.hpp"

class Rules
{
  private:
    bool aces;
    unsigned handsAfterAceSplit;
    bool bjBjPush;
  public:
    Rules();

    std::vector<Action> getActionsNotAllowed(const std::vector<std::vector<unsigned short>> & cards, unsigned handIndex);
    bool blackjackBlackjackPush();
};

#endif
