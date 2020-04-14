#include "../BasicPlayingStrategy.hpp"
#include <gtest/gtest.h>

TEST(BasicPlayingStrategyTest, TestGetCoordinatesHardHands)
{
    BasicPlayingStrategy p;
    EXPECT_EQ(std::vector<unsigned short>({0,3}), p.getCoordinates(std::vector<unsigned short>({2,3,2}), 5));
    EXPECT_EQ(std::vector<unsigned short>({0,9}), p.getCoordinates(std::vector<unsigned short>({2,3,2}), 1));
    EXPECT_EQ(std::vector<unsigned short>({6,3}), p.getCoordinates(std::vector<unsigned short>({8,4,2}), 5));
    EXPECT_EQ(std::vector<unsigned short>({6,9}), p.getCoordinates(std::vector<unsigned short>({8,4,2}), 1));
    EXPECT_EQ(std::vector<unsigned short>({9,5}), p.getCoordinates(std::vector<unsigned short>({8,6,4,2}), 7));
    EXPECT_EQ(std::vector<unsigned short>({9,5}), p.getCoordinates(std::vector<unsigned short>({8,2,4,3}), 7));
}

TEST(BasicPlayingStrategyTest, TestGetCoordinatesHandWithAce)
{
    BasicPlayingStrategy p;
    EXPECT_EQ(std::vector<unsigned short>({4,6}), p.getCoordinates(std::vector<unsigned short>({1,2,3,2,4}), 8));
    EXPECT_EQ(std::vector<unsigned short>({4,8}), p.getCoordinates(std::vector<unsigned short>({1,1,3,6,1}), 10));
}

TEST(BasicPlayingStrategyTest, TestGetCoordinatesSoftHands)
{
    BasicPlayingStrategy p;
    EXPECT_EQ(std::vector<unsigned short>({23,0}), p.getCoordinates(std::vector<unsigned short>({1,3,2}), 2));
    EXPECT_EQ(std::vector<unsigned short>({23,9}), p.getCoordinates(std::vector<unsigned short>({3,1,2}), 1));
    EXPECT_EQ(std::vector<unsigned short>({26,4}), p.getCoordinates(std::vector<unsigned short>({2,4,1,2}), 6));
    EXPECT_EQ(std::vector<unsigned short>({26,9}), p.getCoordinates(std::vector<unsigned short>({2,2,4,1}), 1));
    EXPECT_EQ(std::vector<unsigned short>({21,7}), p.getCoordinates(std::vector<unsigned short>({1,1,2}), 9));
    EXPECT_EQ(std::vector<unsigned short>({22,7}), p.getCoordinates(std::vector<unsigned short>({1,2,1,1}), 9));
}

TEST(BasicPlayingStrategyTest, TestGetCoordinatesPairs)
{
    BasicPlayingStrategy p;
    EXPECT_EQ(std::vector<unsigned short>({13,2}), p.getCoordinates(std::vector<unsigned short>({5,5}), 4));
    EXPECT_EQ(std::vector<unsigned short>({13,9}), p.getCoordinates(std::vector<unsigned short>({5,5}), 1));
    EXPECT_EQ(std::vector<unsigned short>({19,1}), p.getCoordinates(std::vector<unsigned short>({1,1}), 3));
    EXPECT_EQ(std::vector<unsigned short>({19,9}), p.getCoordinates(std::vector<unsigned short>({1,1}), 1));
}

TEST(BasicPlayingStrategyTest, TestGetPlay)
{
    BasicPlayingStrategy p;
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

TEST(BasicPlayingStrategyTest, TestGetPlayWithDoubleDownNotAllowed)
{
    BasicPlayingStrategy p;
    std::vector<Action> notAllowedActions{Action::DOUBLEDOWN};
    EXPECT_EQ(Action::STAND, p.getPlay(std::vector<unsigned short>{1,7}, 3, notAllowedActions));
    EXPECT_EQ(Action::HIT, p.getPlay(std::vector<unsigned short>{1,6}, 3, notAllowedActions));
    EXPECT_EQ(Action::HIT, p.getPlay(std::vector<unsigned short>{1,5}, 4, notAllowedActions));
    EXPECT_EQ(Action::HIT, p.getPlay(std::vector<unsigned short>{6,5}, 5, notAllowedActions));
    EXPECT_EQ(Action::HIT, p.getPlay(std::vector<unsigned short>{5,5}, 6, notAllowedActions));
}

TEST(BasicPlayingStrategyTest, TestGetPlayWithSplitNotAllowed)
{
    BasicPlayingStrategy p;
    std::vector<Action> notAllowedActions{Action::SPLIT};
    EXPECT_EQ(Action::STAND, p.getPlay(std::vector<unsigned short>{7,7}, 6, notAllowedActions));
    EXPECT_EQ(Action::HIT, p.getPlay(std::vector<unsigned short>{7,7}, 7, notAllowedActions));
    EXPECT_EQ(Action::HIT, p.getPlay(std::vector<unsigned short>{7,7}, 8, notAllowedActions));
    EXPECT_EQ(Action::STAND, p.getPlay(std::vector<unsigned short>{8,8}, 6, notAllowedActions));
    EXPECT_EQ(Action::HIT, p.getPlay(std::vector<unsigned short>{8,8}, 1, notAllowedActions));
    EXPECT_EQ(Action::STAND, p.getPlay(std::vector<unsigned short>{9,9}, 2, notAllowedActions));
    EXPECT_EQ(Action::STAND, p.getPlay(std::vector<unsigned short>{9,9}, 10, notAllowedActions));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
