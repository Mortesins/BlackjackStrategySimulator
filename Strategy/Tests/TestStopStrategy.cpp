#include "../StopStrategy.hpp"
#include <gtest/gtest.h>

TEST(StopStrategy, WhenBelowStopAtBudgetThenAlwaysPlay)
{
    StopStrategy s;
    EXPECT_EQ(2, s.getBet(23, 2, 0));  // 0 consecutive losses
    EXPECT_EQ(2, s.getBet(23, 2, 3));  // 3 consecutive losses
    EXPECT_EQ(4, s.getBet(23, 4, 0));  // 0 consecutive losses, bigger bet
    EXPECT_EQ(4, s.getBet(23, 4, 3));  // 3 consecutive losses, bigger bet
}

TEST(StopStrategy, WhenNoConsecutiveLossesThenAlwaysPlay)
{
    StopStrategy s;
    EXPECT_EQ(2, s.getBet(13, 2, 0));
    EXPECT_EQ(4, s.getBet(13, 4, 0));  // bigger bet
    EXPECT_EQ(2, s.getBet(123, 2, 0));
    EXPECT_EQ(4, s.getBet(123, 4, 0));  // bigger bet
}

TEST(StopStrategy, WhenAtStopAtBudgetAndNoConsecutiveLossesThenPlay)
{
    StopStrategy s;
    EXPECT_EQ(2, s.getBet(24, 2, 0));
    EXPECT_EQ(4, s.getBet(24, 4, 0));
}

TEST(StopStrategy, WhenAtStopAtBudgetAndSomeConsecutiveLossesThenStop)
{
    StopStrategy s(24, 2);
    EXPECT_EQ(0, s.getBet(24, 2, 1));
    EXPECT_EQ(0, s.getBet(24, 2, 2));
    EXPECT_EQ(0, s.getBet(24, 4, 1));  // bigger bet
    EXPECT_EQ(0, s.getBet(24, 6, 2));  // bigger bet
}

TEST(StopStrategy, WhenAboveStopAtBudgetAndTwoOrMoreConsecutiveLossesThenStop)
{
    StopStrategy s(24, 2);
    EXPECT_EQ(0, s.getBet(26, 2, 2));
    EXPECT_EQ(0, s.getBet(26, 2, 2));
    EXPECT_EQ(0, s.getBet(26, 4, 2));  // bigger bet
    EXPECT_EQ(0, s.getBet(26, 6, 2));  // bigger bet
    EXPECT_EQ(0, s.getBet(26, 2, 3));
    EXPECT_EQ(0, s.getBet(26, 4, 3));  // bigger bet
}

TEST(StopStrategy, WhenLessThanOneBetAboveStopAtBudgetAndOneConsecutiveLossThenGetOnlyTheExcessAsABet)
{
    StopStrategy s(24, 2);
    EXPECT_EQ(2, s.getBet(26, 2, 1));
    EXPECT_EQ(2, s.getBet(26, 4, 1));
}

TEST(StopStrategy, WhenMoreThanOneBetAboveStopAtBudgetAndOneConsecutiveLossThenPlay)
{
    StopStrategy s(24, 2);
    EXPECT_EQ(2, s.getBet(26, 2, 1));
    EXPECT_EQ(4, s.getBet(28, 4, 1));
    EXPECT_EQ(6, s.getBet(30, 6, 1));
}

TEST(StopStrategy, WhenMoreThanOneBetAboveStopAtBudgetThenCanDouble)
{
    StopStrategy s(24, 2);
    EXPECT_TRUE(s.canDouble(26, 2));
    EXPECT_TRUE(s.canDouble(28, 4));
    EXPECT_TRUE(s.canDouble(30, 6));
}

TEST(StopStrategy, WhenLessThanOneBetAboveStopAtBudgetThenCannotDouble)
{
    StopStrategy s(24, 2);
    EXPECT_FALSE(s.canDouble(26, 4));
    EXPECT_FALSE(s.canDouble(28, 6));
    EXPECT_FALSE(s.canDouble(30, 8));
}

TEST(StopStrategy, WhenAtStopAtBudgetThenCannotDouble)
{
    StopStrategy s(24, 2);
    EXPECT_FALSE(s.canDouble(24, 2));
}

TEST(StopStrategy, WhenBelowStopAtBudgetThenCanDouble)
{
    StopStrategy s(24, 2);
    EXPECT_TRUE(s.canDouble(23, 2));
}

TEST(StopStrategy, WhenMoreThanOneBetAboveStopAtBudgetThenCanSplit)
{
    StopStrategy s(24, 2);
    EXPECT_TRUE(s.canSplit(26, 2));
    EXPECT_TRUE(s.canSplit(28, 4));
    EXPECT_TRUE(s.canSplit(30, 6));
}

TEST(StopStrategy, WhenLessThanOneBetAboveStopAtBudgetThenCannotSplit)
{
    StopStrategy s(24, 2);
    EXPECT_FALSE(s.canSplit(26, 4));
    EXPECT_FALSE(s.canSplit(28, 6));
    EXPECT_FALSE(s.canSplit(30, 8));
}

TEST(StopStrategy, WhenAtStopAtBudgetThenCannotSplit)
{
    StopStrategy s(24, 2);
    EXPECT_FALSE(s.canSplit(24, 2));
}

TEST(StopStrategy, WhenBelowStopAtBudgetThenCanSplit)
{
    StopStrategy s(24, 2);
    EXPECT_TRUE(s.canSplit(23, 2));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
