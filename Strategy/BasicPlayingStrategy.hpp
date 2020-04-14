#ifndef BASIC_PLAYING_STRATEGY_HPP
#define BASIC_PLAYING_STRATEGY_HPP

#include <vector>
#include <algorithm>

#include "PlayingStrategy.hpp"


class BasicPlayingStrategy
    : public PlayingStrategy
{
  public:
    BasicPlayingStrategy();
    static inline bool actionIsAllowed(Action action, const std::vector<Action>& actionsNotAllowed);
    virtual Action getPlay(
        const std::vector<unsigned short>& cards,
        unsigned short dealerUpCard
    ) const;
    virtual Action getPlay(
        const std::vector<unsigned short>& cards,
        unsigned short dealerUpCard,
        const std::vector<Action>& actionsNotAllowed
    ) const;
    virtual Action getPlay(
        const std::vector<unsigned short>& cards,
        unsigned short dealerUpCard,
        double trueCount
    ) const;
    virtual Action getPlay(
        const std::vector<unsigned short>& cards,
        unsigned short dealerUpCard,
        const std::vector<Action>& actionsNotAllowed,
        double trueCount
    ) const;
};


inline bool BasicPlayingStrategy::actionIsAllowed(Action action, const std::vector<Action>& actionsNotAllowed)
{
    return std::find(actionsNotAllowed.begin(), actionsNotAllowed.end(), action) == actionsNotAllowed.end();
}
#endif
