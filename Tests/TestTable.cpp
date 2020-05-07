#include "../Table.hpp"
#include "../PlayerSeat.hpp"
#include "../Player.hpp"
#include "../Strategy/DummyStrategy.hpp"
#include <gtest/gtest.h>

TEST(TableTest, TestGetHandValue)
{
    DummyStrategy d;
    Player p("gigi", 10, d);
    PlayerSeat ps(&p);
    ps.cards = {
        {4, 1, 3},
        {5, 4, 1, 4, 1, 8},
        {4, 3},
        {1, 4, 1, 3}
    };
    EXPECT_EQ(18, getHandValue(ps, 0));
    EXPECT_EQ(23, getHandValue(ps, 1));
    EXPECT_EQ(7, getHandValue(ps, 2));
    EXPECT_EQ(19, getHandValue(ps, 3));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
