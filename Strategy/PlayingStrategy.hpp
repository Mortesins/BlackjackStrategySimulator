#ifndef PLAYING_STRATEGY_HPP
#define PLAYING_STRATEGY_HPP

#include <vector>

#include "../Action.hpp"

class PlayingStrategy
{
  private:
    void printActionRow(unsigned row) const;

  protected:
    std::vector<std::vector<std::vector<Action>>> actionsTable;

  public:
    virtual ~PlayingStrategy() {};
    //returns row and column of table
    std::vector<unsigned short> getCoordinates(
        const std::vector<unsigned short>& cards,
        unsigned short dealerUpCard
    ) const;

    virtual void printStrategy() const;
    virtual Action getPlay(
        const std::vector<unsigned short>& cards,
        unsigned short dealerUpCard
    ) const = 0;
    virtual Action getPlay(
        const std::vector<unsigned short>& cards,
        unsigned short dealerUpCard,
        const std::vector<Action>& actionsNotAllowed
    ) const = 0;

    virtual Action getPlay(
        const std::vector<unsigned short>& cards,
        unsigned short dealerUpCard,
        double trueCount
    ) const = 0;
    virtual Action getPlay(
        const std::vector<unsigned short>& cards,
        unsigned short dealerUpCard,
        const std::vector<Action>& actionsNotAllowed,
        double trueCount
    ) const = 0;
};

#endif
