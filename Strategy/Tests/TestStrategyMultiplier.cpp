#include "../StrategyMultiplier.hpp"
#include <gtest/gtest.h>
#include "../../Constants.hpp"

namespace
{
    unsigned BUDGET = 30*MINIMUM_BET;  // Above stopAtBudget
}

TEST(StrategyMultiplier, WhenStreakIsZeroThenGetBetReturnsBasedOnMultipliers)
{
    StrategyMultiplier s;
    EXPECT_EQ(2, s.getBet(0.0, BUDGET, 0));
    EXPECT_EQ(2, s.getBet(-1.0, BUDGET, 0));
    EXPECT_EQ(0, s.getBet(-2.0, BUDGET, 0));
    EXPECT_EQ(0, s.getBet(-3.0, BUDGET, 0));
    EXPECT_EQ(2, s.getBet(1.0, BUDGET, 0));
    EXPECT_EQ(2, s.getBet(2.0, BUDGET, 0));
    EXPECT_EQ(4, s.getBet(2.1, BUDGET, 0));
}

TEST(StrategyMultiplier, WhenStreakIsNegativeTwoThenGetBetIsZeroBecauseStopStrategyIsCalled)
{
    StrategyMultiplier s;
    EXPECT_EQ(0, s.getBet(3.0, BUDGET, -2));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
