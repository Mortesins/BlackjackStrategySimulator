#ifndef RULES_HPP
#define RULES_HPP

#include <vector>

#include "Action.hpp"

class Rules
{
  private:
    const bool bjBjPush;
    const bool splitAcesPaid1To1;
    bool aces;
    unsigned handsAfterAceSplit;
    std::vector<Action> actionsNotAllowedTemplate; // Contains never allowed actions plus SPLIT which can be removed
  public:
    Rules();

    std::vector<Action> getActionsNotAllowed(const std::vector<std::vector<unsigned short>>& cards, unsigned handIndex);
    bool blackjackBlackjackPush() const;
    bool splitAcesPaidOneToOne() const;
};

#endif
