#include "IndexedPlayingStrategy.hpp"
#include "StrategyExpections.hpp"

IndexedPlayingStrategy::IndexedPlayingStrategy()
{
    // TODO: finish writing the complete strategy
    for (unsigned i = 0; i < 10; ++i)
    {
        for (unsigned j = 0; j < 28; ++j)
        {
            indices[j][i] = 0;
            isIndexed[j][i] = false;
        }
    }
    // 2-2
    isIndexed[10][0] = true;
    isIndexed[10][1] = true;
    isIndexed[10][2] = true;
    isIndexed[10][3] = true;
    isIndexed[10][4] = true;
    indices[10][0] = 7;
    indices[10][1] = 3;
    indices[10][2] = 0;
    indices[10][3] = -4;
    indices[10][4] = -9;
    // 8-8
    isIndexed[16][8] = true;
    indices[16][8] = 6;
    actionsTable[16][8] = std::vector<Action>{Action::HIT, Action::SPLIT}; // reverse: split only if lower than 6
}

Action IndexedPlayingStrategy::getPlay(const std::vector<unsigned short>& cards, unsigned short dealerUpCard) const
{
    std::vector<Action> emptyActionsNotAllowed;
    return getPlay(cards, dealerUpCard, emptyActionsNotAllowed, 0);
}

Action IndexedPlayingStrategy::getPlay(
    const std::vector<unsigned short>& cards,
    unsigned short dealerUpCard,
    const std::vector<Action>& actionsNotAllowed
) const
{
    return getPlay(cards, dealerUpCard, actionsNotAllowed, 0);
}

Action IndexedPlayingStrategy::getPlay(
    const std::vector<unsigned short>& cards,
    unsigned short dealerUpCard,
    double trueCount
) const
{
    std::vector<Action> emptyActionsNotAllowed;
    return getPlay(cards, dealerUpCard, emptyActionsNotAllowed, trueCount);
}

Action IndexedPlayingStrategy::getPlay(
    const std::vector<unsigned short>& cards,
    unsigned short dealerUpCard,
    const std::vector<Action>& actionsNotAllowed,
    double trueCount
) const
{
    std::vector<unsigned short> coord = getCoordinates(cards, dealerUpCard);

    Action firstAction = actionsTable[coord[0]][coord[1]][0];
    Action secondAction = actionsTable[coord[0]][coord[1]][1];
    if (not actionIsAllowed(firstAction, actionsNotAllowed))
    {
        return secondAction;
    }
    else if (not actionIsAllowed(secondAction, actionsNotAllowed))
    {
        return firstAction;
    }
    else
    {
        if
        (
            not isIndexed[coord[0]][coord[1]]
            || ( isIndexed[coord[0]][coord[1]] && trueCount > indices[coord[0]][coord[1]] )
        )
        {
            return firstAction;
        }
        else
        {
            return secondAction;
        }
    }
    throw StrategyError(
        "IndexedPlayingStrategy::getPlay():\n"
        "\t\t\tLooped through all possible actions but no action found in getPlay. Something went wrong!"
    );
}
