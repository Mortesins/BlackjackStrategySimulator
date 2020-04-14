#include "../IndexedPlayingStrategy.hpp"
#include <gtest/gtest.h>

TEST(IndexedPlayingStrategy, TestGetPlayWithoutTrueCount)
{
    IndexedPlayingStrategy p;
    EXPECT_EQ(Action::STAND, p.getPlay(std::vector<unsigned short>{10,3}, 3));
    EXPECT_EQ(Action::STAND, p.getPlay(std::vector<unsigned short>{10,3,4}, 3));
    EXPECT_EQ(Action::SPLIT, p.getPlay(std::vector<unsigned short>{8,8}, 6));
    EXPECT_EQ(Action::HIT, p.getPlay(std::vector<unsigned short>{2,2,4}, 8));
    EXPECT_EQ(Action::DOUBLEDOWN, p.getPlay(std::vector<unsigned short>{9,2}, 3));
    EXPECT_EQ(Action::SPLIT, p.getPlay(std::vector<unsigned short>{3,3}, 4));
    EXPECT_EQ(Action::HIT, p.getPlay(std::vector<unsigned short>{1,6}, 1));
    EXPECT_EQ(Action::HIT, p.getPlay(std::vector<unsigned short>{1,6}, 2));
    EXPECT_EQ(Action::DOUBLEDOWN, p.getPlay(std::vector<unsigned short>{1,6}, 3));
    EXPECT_EQ(Action::HIT, p.getPlay(std::vector<unsigned short>{1,6}, 9));
    EXPECT_EQ(Action::HIT, p.getPlay(std::vector<unsigned short>{6,6}, 1));
    EXPECT_EQ(Action::STAND, p.getPlay(std::vector<unsigned short>{1,8}, 6));
    EXPECT_EQ(Action::HIT, p.getPlay(std::vector<unsigned short>{1,2}, 3));
    EXPECT_EQ(Action::HIT, p.getPlay(std::vector<unsigned short>{9,2,4}, 8));
    EXPECT_EQ(Action::DOUBLEDOWN, p.getPlay(std::vector<unsigned short>{1,4}, 5));
    EXPECT_EQ(Action::DOUBLEDOWN, p.getPlay(std::vector<unsigned short>{5,5}, 5));
    EXPECT_EQ(Action::STAND, p.getPlay(std::vector<unsigned short>{9,9}, 7));
}

TEST(IndexedPlayingStrategy, TestGetPlayWithTrueCount)
{
    IndexedPlayingStrategy p;
    EXPECT_EQ(Action::SPLIT, p.getPlay(std::vector<unsigned short>{2,2}, 3, 3.1));
    EXPECT_EQ(Action::HIT, p.getPlay(std::vector<unsigned short>{2,2}, 3, 3.0));
    EXPECT_EQ(Action::HIT, p.getPlay(std::vector<unsigned short>{2,2}, 3, 2.9));
    EXPECT_EQ(Action::SPLIT, p.getPlay(std::vector<unsigned short>{2,2}, 4, 0.1));
    EXPECT_EQ(Action::HIT, p.getPlay(std::vector<unsigned short>{2,2}, 4, 0.0));
    EXPECT_EQ(Action::HIT, p.getPlay(std::vector<unsigned short>{2,2}, 4, -0.1));
    EXPECT_EQ(Action::SPLIT, p.getPlay(std::vector<unsigned short>{2,2}, 6, -6.0));
    EXPECT_EQ(Action::HIT, p.getPlay(std::vector<unsigned short>{2,2}, 6, -9.0));
    EXPECT_EQ(Action::HIT, p.getPlay(std::vector<unsigned short>{2,2}, 6, -12.9));
    EXPECT_EQ(Action::SPLIT, p.getPlay(std::vector<unsigned short>{2,2}, 7, 10.0));
    EXPECT_EQ(Action::SPLIT, p.getPlay(std::vector<unsigned short>{2,2}, 7, 9.0));
    EXPECT_EQ(Action::SPLIT, p.getPlay(std::vector<unsigned short>{2,2}, 7, -2.9));

    EXPECT_EQ(Action::SPLIT, p.getPlay(std::vector<unsigned short>{8,8}, 9, -2.9));
    EXPECT_EQ(Action::HIT, p.getPlay(std::vector<unsigned short>{8,8}, 10, 6.1));
    EXPECT_EQ(Action::SPLIT, p.getPlay(std::vector<unsigned short>{8,8}, 10, 6.0));
    EXPECT_EQ(Action::SPLIT, p.getPlay(std::vector<unsigned short>{8,8}, 10, 5.9));
}

TEST(IndexedPlayingStrategy, TestGetPlayWithTrueCountWithSplitNotAllowed)
{
    IndexedPlayingStrategy p;
    std::vector<Action> actionsNotAllowed{Action::SPLIT};
    EXPECT_EQ(Action::HIT, p.getPlay(std::vector<unsigned short>{2,2}, 3, actionsNotAllowed, 3.1));
    EXPECT_EQ(Action::HIT, p.getPlay(std::vector<unsigned short>{2,2}, 3, actionsNotAllowed, 3.0));
    EXPECT_EQ(Action::HIT, p.getPlay(std::vector<unsigned short>{2,2}, 6, actionsNotAllowed, -6.0));
    EXPECT_EQ(Action::HIT, p.getPlay(std::vector<unsigned short>{2,2}, 6, actionsNotAllowed, -9.0));
    EXPECT_EQ(Action::HIT, p.getPlay(std::vector<unsigned short>{2,2}, 7, actionsNotAllowed, 10.0));
    EXPECT_EQ(Action::HIT, p.getPlay(std::vector<unsigned short>{2,2}, 7, actionsNotAllowed, -2.9));

    EXPECT_EQ(Action::HIT, p.getPlay(std::vector<unsigned short>{8,8}, 9, actionsNotAllowed, -2.9));
    EXPECT_EQ(Action::HIT, p.getPlay(std::vector<unsigned short>{8,8}, 10, actionsNotAllowed, 6.1));
    EXPECT_EQ(Action::HIT, p.getPlay(std::vector<unsigned short>{8,8}, 10, actionsNotAllowed, 6.0));
    EXPECT_EQ(Action::HIT, p.getPlay(std::vector<unsigned short>{8,8}, 10, actionsNotAllowed, 5.9));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
