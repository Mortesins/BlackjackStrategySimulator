#include "../Dealer.hpp"
#include <gtest/gtest.h>

TEST(DealerTest, TestGetHandWhenHardHand)
{
    Dealer d;
    d.newCard(9);
    d.newCard(6);
    EXPECT_EQ(15, d.getHand());
}

TEST(DealerTest, TestGetHandWhenSoftHand)
{
    Dealer d;
    d.newCard(1);
    d.newCard(6);
    EXPECT_EQ(17, d.getHand());
    d.newCard(5);
    EXPECT_EQ(12, d.getHand());
}

TEST(DealerTest, WhenTenPlusAceThenBlackjackIsTrue)
{
    Dealer d;
    d.newCard(1);
    d.newCard(10);
    EXPECT_TRUE(d.blackjack());
}

TEST(DealerTest, WhenTwentyOneButNoBlackjackThenBlackjackIsFalse)
{
    Dealer d;
    d.newCard(10);
    d.newCard(9);
    d.newCard(2);
    EXPECT_FALSE(d.blackjack());
    d.reset();
    d.newCard(10);
    d.newCard(10);
    d.newCard(1);
    EXPECT_FALSE(d.blackjack());
}

TEST(DealerTest, WhenNotTwentyOneThenBlackjackIsFalse)
{
    Dealer d;
    d.newCard(10);
    d.newCard(10);
    EXPECT_FALSE(d.blackjack());
}

TEST(DealerTest, WhenNoSoftHitAndLowerThan17ThenHit)
{
    Dealer d;
    d.newCard(10);
    d.newCard(6);
    EXPECT_TRUE(d.hit());
}

TEST(DealerTest, WhenNoSoftHitAndHard17ThenStand)
{
    Dealer d;
    d.newCard(10);
    d.newCard(7);
    EXPECT_FALSE(d.hit());
}

TEST(DealerTest, WhenNoSoftHitAndSoft17ThenStand)
{
    Dealer d;
    d.newCard(1);
    d.newCard(6);
    EXPECT_FALSE(d.hit());
}

TEST(DealerTest, WhenNoSoftHitAndHigherThan17ThenStand)
{
    Dealer d;
    d.newCard(10);
    d.newCard(8);
    EXPECT_FALSE(d.hit());
    d.reset();
    d.newCard(1);
    d.newCard(7);
    EXPECT_FALSE(d.hit());
}

TEST(DealerTest, WhenSoftHitAndSoft17ThenHit)
{
    Dealer d(true); // soft hit
    d.newCard(1);
    d.newCard(6);
    EXPECT_TRUE(d.hit());
}

TEST(DealerTest, WhenSoftHitAndSoft18ThenStand)
{
    Dealer d(true); // soft hit
    d.newCard(7);
    d.newCard(1);
    EXPECT_FALSE(d.hit());
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
