#include "BasicPlayingStrategy.hpp"

BasicPlayingStrategy::BasicPlayingStrategy()
{
    actionsTable = {
        // 0: 8
        {
            {Action::HIT}, // 2
            {Action::HIT}, // 3
            {Action::HIT}, // 4
            {Action::HIT}, // 5
            {Action::HIT}, // 6
            {Action::HIT}, // 7
            {Action::HIT}, // 8
            {Action::HIT}, // 9
            {Action::HIT}, // 10
            {Action::HIT}  // A
        },
        // 1: 9
        {
            {Action::HIT}, // 2
            {Action::DOUBLEDOWN, Action::HIT}, // 3
            {Action::DOUBLEDOWN, Action::HIT}, // 4
            {Action::DOUBLEDOWN, Action::HIT}, // 5
            {Action::DOUBLEDOWN, Action::HIT}, // 6
            {Action::HIT}, // 7
            {Action::HIT}, // 8
            {Action::HIT}, // 9
            {Action::HIT}, // 10
            {Action::HIT}  // A
        },
        // 2: 10
        {
            {Action::DOUBLEDOWN, Action::HIT}, // 2
            {Action::DOUBLEDOWN, Action::HIT}, // 3
            {Action::DOUBLEDOWN, Action::HIT}, // 4
            {Action::DOUBLEDOWN, Action::HIT}, // 5
            {Action::DOUBLEDOWN, Action::HIT}, // 6
            {Action::DOUBLEDOWN, Action::HIT}, // 7
            {Action::DOUBLEDOWN, Action::HIT}, // 8
            {Action::DOUBLEDOWN, Action::HIT}, // 9
            {Action::HIT}, // 10
            {Action::HIT}  // A
        },
        // 3: 11
        {
            {Action::DOUBLEDOWN, Action::HIT}, // 2
            {Action::DOUBLEDOWN, Action::HIT}, // 3
            {Action::DOUBLEDOWN, Action::HIT}, // 4
            {Action::DOUBLEDOWN, Action::HIT}, // 5
            {Action::DOUBLEDOWN, Action::HIT}, // 6
            {Action::DOUBLEDOWN, Action::HIT}, // 7
            {Action::DOUBLEDOWN, Action::HIT}, // 8
            {Action::DOUBLEDOWN, Action::HIT}, // 9
            {Action::DOUBLEDOWN, Action::HIT}, // 10
            {Action::HIT}  // A
        },
        // 4: 12
        {
            {Action::HIT}, // 2
            {Action::HIT}, // 3
            {Action::STAND}, // 4
            {Action::STAND}, // 5
            {Action::STAND}, // 6
            {Action::HIT}, // 7
            {Action::HIT}, // 8
            {Action::HIT}, // 9
            {Action::HIT}, // 10
            {Action::HIT}  // A
        },
        // 5: 13
        {
            {Action::STAND}, // 2
            {Action::STAND}, // 3
            {Action::STAND}, // 4
            {Action::STAND}, // 5
            {Action::STAND}, // 6
            {Action::HIT}, // 7
            {Action::HIT}, // 8
            {Action::HIT}, // 9
            {Action::HIT}, // 10
            {Action::HIT}  // A
        },
        // 6: 14
        {
            {Action::STAND}, // 2
            {Action::STAND}, // 3
            {Action::STAND}, // 4
            {Action::STAND}, // 5
            {Action::STAND}, // 6
            {Action::HIT}, // 7
            {Action::HIT}, // 8
            {Action::HIT}, // 9
            {Action::HIT}, // 10
            {Action::HIT}  // A
        },
        // 7: 15
        {
            {Action::STAND}, // 2
            {Action::STAND}, // 3
            {Action::STAND}, // 4
            {Action::STAND}, // 5
            {Action::STAND}, // 6
            {Action::HIT}, // 7
            {Action::HIT}, // 8
            {Action::HIT}, // 9
            {Action::HIT}, // 10
            {Action::HIT}  // A
        },
        // 8: 16
        {
            {Action::STAND}, // 2
            {Action::STAND}, // 3
            {Action::STAND}, // 4
            {Action::STAND}, // 5
            {Action::STAND}, // 6
            {Action::HIT}, // 7
            {Action::HIT}, // 8
            {Action::HIT}, // 9
            {Action::HIT}, // 10
            {Action::HIT}  // A
        },
        // 9: 17
        {
            {Action::STAND}, // 2
            {Action::STAND}, // 3
            {Action::STAND}, // 4
            {Action::STAND}, // 5
            {Action::STAND}, // 6
            {Action::STAND}, // 7
            {Action::STAND}, // 8
            {Action::STAND}, // 9
            {Action::STAND}, // 10
            {Action::STAND}  // A
        },
        // 10: 2-2
        {
            {Action::SPLIT, Action::HIT}, // 2
            {Action::SPLIT, Action::HIT}, // 3
            {Action::SPLIT, Action::HIT}, // 4
            {Action::SPLIT, Action::HIT}, // 5
            {Action::SPLIT, Action::HIT}, // 6
            {Action::SPLIT, Action::HIT}, // 7
            {Action::HIT}, // 8
            {Action::HIT}, // 9
            {Action::HIT}, // 10
            {Action::HIT}  // A
        },
        // 11: 3-3
        {
            {Action::SPLIT, Action::HIT}, // 2
            {Action::SPLIT, Action::HIT}, // 3
            {Action::SPLIT, Action::HIT}, // 4
            {Action::SPLIT, Action::HIT}, // 5
            {Action::SPLIT, Action::HIT}, // 6
            {Action::SPLIT, Action::HIT}, // 7
            {Action::HIT}, // 8
            {Action::HIT}, // 9
            {Action::HIT}, // 10
            {Action::HIT}  // A
        },
        // 12: 4-4
        {
            {Action::HIT}, // 2
            {Action::HIT}, // 3
            {Action::HIT}, // 4
            {Action::SPLIT, Action::HIT}, // 5
            {Action::SPLIT, Action::HIT}, // 6
            {Action::HIT}, // 7
            {Action::HIT}, // 8
            {Action::HIT}, // 9
            {Action::HIT}, // 10
            {Action::HIT}  // A
        },
        // 13: 5-5
        {
            {Action::DOUBLEDOWN, Action::HIT}, // 2
            {Action::DOUBLEDOWN, Action::HIT}, // 3
            {Action::DOUBLEDOWN, Action::HIT}, // 4
            {Action::DOUBLEDOWN, Action::HIT}, // 5
            {Action::DOUBLEDOWN, Action::HIT}, // 6
            {Action::DOUBLEDOWN, Action::HIT}, // 7
            {Action::DOUBLEDOWN, Action::HIT}, // 8
            {Action::DOUBLEDOWN, Action::HIT}, // 9
            {Action::HIT}, // 10
            {Action::HIT}  // A
        },
        // 14: 6-6
        {
            {Action::SPLIT, Action::HIT}, // 2
            {Action::SPLIT, Action::HIT}, // 3
            {Action::SPLIT, Action::STAND}, // 4
            {Action::SPLIT, Action::STAND}, // 5
            {Action::SPLIT, Action::STAND}, // 6
            {Action::HIT}, // 7
            {Action::HIT}, // 8
            {Action::HIT}, // 9
            {Action::HIT}, // 10
            {Action::HIT}  // A
        },
        // 15: 7-7
        {
            {Action::SPLIT, Action::STAND}, // 2
            {Action::SPLIT, Action::STAND}, // 3
            {Action::SPLIT, Action::STAND}, // 4
            {Action::SPLIT, Action::STAND}, // 5
            {Action::SPLIT, Action::STAND}, // 6
            {Action::SPLIT, Action::HIT}, // 7
            {Action::HIT}, // 8
            {Action::HIT}, // 9
            {Action::HIT}, // 10
            {Action::HIT}  // A
        },
        // 16: 8-8
        {
            {Action::SPLIT, Action::STAND}, // 2
            {Action::SPLIT, Action::STAND}, // 3
            {Action::SPLIT, Action::STAND}, // 4
            {Action::SPLIT, Action::STAND}, // 5
            {Action::SPLIT, Action::STAND}, // 6
            {Action::SPLIT, Action::HIT}, // 7
            {Action::SPLIT, Action::HIT}, // 8
            {Action::SPLIT, Action::HIT}, // 9
            {Action::SPLIT, Action::HIT}, // 10
            {Action::SPLIT, Action::HIT}  // A
        },
        // 17: 9-9
        {
            {Action::SPLIT, Action::STAND}, // 2
            {Action::SPLIT, Action::STAND}, // 3
            {Action::SPLIT, Action::STAND}, // 4
            {Action::SPLIT, Action::STAND}, // 5
            {Action::SPLIT, Action::STAND}, // 6
            {Action::STAND}, // 7
            {Action::SPLIT, Action::STAND}, // 8
            {Action::SPLIT, Action::STAND}, // 9
            {Action::STAND}, // 10
            {Action::STAND}  // A
        },
        // 18: 10-10
        {
            {Action::STAND}, // 2
            {Action::STAND}, // 3
            {Action::STAND}, // 4
            {Action::STAND}, // 5
            {Action::STAND}, // 6
            {Action::STAND}, // 7
            {Action::STAND}, // 8
            {Action::STAND}, // 9
            {Action::STAND}, // 10
            {Action::STAND}  // A
        },
        // 19: A-A
        {
            {Action::SPLIT, Action::HIT}, // 2
            {Action::SPLIT, Action::HIT}, // 3
            {Action::SPLIT, Action::HIT}, // 4
            {Action::SPLIT, Action::HIT}, // 5
            {Action::SPLIT, Action::HIT}, // 6
            {Action::SPLIT, Action::HIT}, // 7
            {Action::SPLIT, Action::HIT}, // 8
            {Action::SPLIT, Action::HIT}, // 9
            {Action::SPLIT, Action::HIT}, // 10
            {Action::SPLIT, Action::HIT}  // A
        },
        // 20: A-2
        {
            {Action::HIT}, // 2
            {Action::HIT}, // 3
            {Action::HIT}, // 4
            {Action::HIT}, // 5
            {Action::DOUBLEDOWN, Action::HIT}, // 6
            {Action::HIT}, // 7
            {Action::HIT}, // 8
            {Action::HIT}, // 9
            {Action::HIT}, // 10
            {Action::HIT}  // A
        },
        // 21: A-3
        {
            {Action::HIT}, // 2
            {Action::HIT}, // 3
            {Action::HIT}, // 4
            {Action::DOUBLEDOWN, Action::HIT}, // 5
            {Action::DOUBLEDOWN, Action::HIT}, // 6
            {Action::HIT}, // 7
            {Action::HIT}, // 8
            {Action::HIT}, // 9
            {Action::HIT}, // 10
            {Action::HIT}  // A
        },
        // 22: A-4
        {
            {Action::HIT}, // 2
            {Action::HIT}, // 3
            {Action::DOUBLEDOWN, Action::HIT}, // 4
            {Action::DOUBLEDOWN, Action::HIT}, // 5
            {Action::DOUBLEDOWN, Action::HIT}, // 6
            {Action::HIT}, // 7
            {Action::HIT}, // 8
            {Action::HIT}, // 9
            {Action::HIT}, // 10
            {Action::HIT}  // A
        },
        // 23: A-5
        {
            {Action::HIT}, // 2
            {Action::HIT}, // 3
            {Action::DOUBLEDOWN, Action::HIT}, // 4
            {Action::DOUBLEDOWN, Action::HIT}, // 5
            {Action::DOUBLEDOWN, Action::HIT}, // 6
            {Action::HIT}, // 7
            {Action::HIT}, // 8
            {Action::HIT}, // 9
            {Action::HIT}, // 10
            {Action::HIT}  // A
        },
        // 24: A-6
        {
            {Action::HIT}, // 2
            {Action::DOUBLEDOWN, Action::HIT}, // 3
            {Action::DOUBLEDOWN, Action::HIT}, // 4
            {Action::DOUBLEDOWN, Action::HIT}, // 5
            {Action::DOUBLEDOWN, Action::HIT}, // 6
            {Action::HIT}, // 7
            {Action::HIT}, // 8
            {Action::HIT}, // 9
            {Action::HIT}, // 10
            {Action::HIT}  // A
        },
        // 25: A-7
        {
            {Action::STAND}, // 2
            {Action::DOUBLEDOWN, Action::STAND}, // 3
            {Action::DOUBLEDOWN, Action::STAND}, // 4
            {Action::DOUBLEDOWN, Action::STAND}, // 5
            {Action::DOUBLEDOWN, Action::STAND}, // 6
            {Action::STAND}, // 7
            {Action::STAND}, // 8
            {Action::HIT}, // 9
            {Action::HIT}, // 10
            {Action::HIT}  // A
        },
        // 26: A-8
        {
            {Action::STAND}, // 2
            {Action::STAND}, // 3
            {Action::STAND}, // 4
            {Action::STAND}, // 5
            {Action::STAND}, // 6
            {Action::STAND}, // 7
            {Action::STAND}, // 8
            {Action::STAND}, // 9
            {Action::STAND}, // 10
            {Action::STAND}  // A
        },
        // 27: A-9
        {
            {Action::STAND}, // 2
            {Action::STAND}, // 3
            {Action::STAND}, // 4
            {Action::STAND}, // 5
            {Action::STAND}, // 6
            {Action::STAND}, // 7
            {Action::STAND}, // 8
            {Action::STAND}, // 9
            {Action::STAND}, // 10
            {Action::STAND}  // A
        },
    };
}

Action BasicPlayingStrategy::getPlay(const std::vector<unsigned short>& cards, unsigned short dealerUpCard) const
{
    std::vector<Action> emptyActionsNotAllowed;
    return getPlay(cards, dealerUpCard, emptyActionsNotAllowed, 0);
}

Action BasicPlayingStrategy::getPlay(
    const std::vector<unsigned short>& cards,
    unsigned short dealerUpCard,
    const std::vector<Action>& actionsNotAllowed
) const
{
    return getPlay(cards, dealerUpCard, actionsNotAllowed, 0);
}

Action BasicPlayingStrategy::getPlay(
    const std::vector<unsigned short>& cards,
    unsigned short dealerUpCard,
    double trueCount
) const
{
    std::vector<Action> emptyActionsNotAllowed;
    return getPlay(cards, dealerUpCard, emptyActionsNotAllowed, trueCount);
}

Action BasicPlayingStrategy::getPlay(
    const std::vector<unsigned short>& cards,
    unsigned short dealerUpCard,
    const std::vector<Action>& actionsNotAllowed,
    double trueCount
) const
{
    std::vector<unsigned short> coord = getCoordinates(cards, dealerUpCard);

    for (Action action : actionsTable[coord[0]][coord[1]])
    {
        if (actionIsAllowed(action, actionsNotAllowed))
        {
            return action;
        }
    }
    throw "Looped through all possible action but no action found in getPlay. Something went wrong!";
}
