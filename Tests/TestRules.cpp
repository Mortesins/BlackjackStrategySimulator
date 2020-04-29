#include "../Rules.hpp"
#include <gtest/gtest.h>

#include <algorithm>

namespace
{
template <class T>
bool compareVectors(std::vector<T> a, std::vector<T> b)
{
   if (a.size() != b.size())
   {
      return false;
   }
   std::sort(a.begin(), a.end());
   std::sort(b.begin(), b.end());
   return (a == b);
}
}

TEST(RulesTest, TestGenericHardHands)
{
    Rules r;
    std::vector<std::vector<unsigned short>> hands = {{5, 9}, {4, 8}, {3, 4, 2}, {9, 8}};
    EXPECT_TRUE(compareVectors(
        {Action::SPLIT, Action::SURRENDER},
        r.getActionsNotAllowed(hands, 0)
    ));
    EXPECT_TRUE(compareVectors(
        {Action::SPLIT, Action::SURRENDER},
        r.getActionsNotAllowed(hands, 1)
    ));
    EXPECT_TRUE(compareVectors(
        {Action::SPLIT, Action::SURRENDER, Action::DOUBLEDOWN},
        r.getActionsNotAllowed(hands, 2)
    ));
    EXPECT_TRUE(compareVectors(
        {Action::SPLIT, Action::SURRENDER},
        r.getActionsNotAllowed(hands, 3)
    ));
}

TEST(RulesTest, WhenTwoSplittableHandsThenOnlySurrenderIsNotAllowed)
{
    Rules r;
    std::vector<std::vector<unsigned short>> hands = {{9, 9}, {9, 9}};
    EXPECT_TRUE(compareVectors(
        {Action::SURRENDER},
        r.getActionsNotAllowed(hands, 0)
    ));
    EXPECT_TRUE(compareVectors(
        {Action::SURRENDER},
        r.getActionsNotAllowed(hands, 1)
    ));
}

TEST(RulesTest, WhenFourSplittableHandsThenCannotSplit)
{
    Rules r;
    std::vector<std::vector<unsigned short>> hands = {{9, 9}, {9, 9}, {9, 9}, {9, 9}};
    EXPECT_TRUE(compareVectors(
        {Action::SPLIT, Action::SURRENDER},
        r.getActionsNotAllowed(hands, 0)
    ));
    EXPECT_TRUE(compareVectors(
        {Action::SPLIT, Action::SURRENDER},
        r.getActionsNotAllowed(hands, 1)
    ));
    EXPECT_TRUE(compareVectors(
        {Action::SPLIT, Action::SURRENDER},
        r.getActionsNotAllowed(hands, 2)
    ));
    EXPECT_TRUE(compareVectors(
        {Action::SPLIT, Action::SURRENDER},
        r.getActionsNotAllowed(hands, 3)
    ));
}

TEST(RulesTest, SplitUpToFourScenario)
{
    Rules r;
    std::vector<std::vector<unsigned short>> hands = {{9, 9}};
    EXPECT_TRUE(compareVectors(
        {Action::SURRENDER},
        r.getActionsNotAllowed(hands, 0)
    ));
    hands = {{9, 9}, {9, 8}};
    EXPECT_TRUE(compareVectors(
        {Action::SURRENDER},
        r.getActionsNotAllowed(hands, 0)
    ));
    EXPECT_TRUE(compareVectors(
        {Action::SPLIT, Action::SURRENDER},
        r.getActionsNotAllowed(hands, 1)
    ));
    hands = {{9, 9}, {9, 9}, {9, 8}};
    EXPECT_TRUE(compareVectors(
        {Action::SURRENDER},
        r.getActionsNotAllowed(hands, 0)
    ));
    EXPECT_TRUE(compareVectors(
        {Action::SURRENDER},
        r.getActionsNotAllowed(hands, 1)
    ));
    EXPECT_TRUE(compareVectors(
        {Action::SPLIT, Action::SURRENDER},
        r.getActionsNotAllowed(hands, 2)
    ));
    hands = {{9, 1}, {9, 10}, {9, 9}, {9, 8}};
    EXPECT_TRUE(compareVectors(
        {Action::SPLIT, Action::SURRENDER},
        r.getActionsNotAllowed(hands, 0)
    ));
    EXPECT_TRUE(compareVectors(
        {Action::SPLIT, Action::SURRENDER},
        r.getActionsNotAllowed(hands, 1)
    ));
    EXPECT_TRUE(compareVectors(
        {Action::SPLIT, Action::SURRENDER},
        r.getActionsNotAllowed(hands, 2)
    ));
    EXPECT_TRUE(compareVectors(
        {Action::SPLIT, Action::SURRENDER},
        r.getActionsNotAllowed(hands, 3)
    ));
}

TEST(RulesTest, SplitAcesScenario)
{
    Rules r;
    std::vector<std::vector<unsigned short>> hands = {{1, 1}};
    EXPECT_TRUE(compareVectors(
        {Action::SURRENDER},
        r.getActionsNotAllowed(hands, 0)
    ));
    hands = {{1, 9}, {1, 8}};
    EXPECT_TRUE(compareVectors(
        {Action::SURRENDER, Action::SPLIT, Action::DOUBLEDOWN, Action::HIT},
        r.getActionsNotAllowed(hands, 0)
    ));
    EXPECT_TRUE(compareVectors(
        {Action::SURRENDER, Action::SPLIT, Action::DOUBLEDOWN, Action::HIT},
        r.getActionsNotAllowed(hands, 1)
    ));
    // another player's hand
    hands = {{8, 1}};
    EXPECT_TRUE(compareVectors(
        {Action::SURRENDER, Action::SPLIT},
        r.getActionsNotAllowed(hands, 0)
    ));
    // another player's hand with again aces
    hands = {{1, 1}};
    EXPECT_TRUE(compareVectors(
        {Action::SURRENDER},
        r.getActionsNotAllowed(hands, 0)
    ));
    hands = {{1, 4}, {1, 1}};
    EXPECT_TRUE(compareVectors(
        {Action::SURRENDER, Action::SPLIT, Action::DOUBLEDOWN, Action::HIT},
        r.getActionsNotAllowed(hands, 0)
    ));
    EXPECT_TRUE(compareVectors(
        {Action::SURRENDER, Action::SPLIT, Action::DOUBLEDOWN, Action::HIT},
        r.getActionsNotAllowed(hands, 1)
    ));
}

TEST(RulesTest, NoSplitAcesScenario)
{
    Rules r;
    std::vector<std::vector<unsigned short>> hands = {{1, 1}};
    EXPECT_TRUE(compareVectors(
        {Action::SURRENDER},
        r.getActionsNotAllowed(hands, 0)
    ));
    hands = {{1, 1, 4}};
    EXPECT_TRUE(compareVectors(
        {Action::SURRENDER, Action::SPLIT, Action::DOUBLEDOWN},
        r.getActionsNotAllowed(hands, 0)
    ));
    // another player's hand
    hands = {{1, 1}};
    EXPECT_TRUE(compareVectors(
        {Action::SURRENDER},
        r.getActionsNotAllowed(hands, 0)
    ));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
