#ifndef INDEXED_PLAYING_STRATEGY_HPP
#define INDEXED_PLAYING_STRATEGY_HPP

#include "BasicPlayingStrategy.hpp"

class IndexedPlayingStrategy
    : public BasicPlayingStrategy
{
  protected:
    double indices[28][10];
    bool isIndexed[28][10];

  public:
    IndexedPlayingStrategy();
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

#endif
