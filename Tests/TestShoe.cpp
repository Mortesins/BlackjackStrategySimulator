#include "../Shoe.hpp"
#include <gtest/gtest.h>
#include <algorithm>

TEST(ShoeTest, TestCardsRemaining)
{
    Shoe s(1, 1.0); // 1 deck, 100% penetration
    EXPECT_EQ(52, s.cardsRemaining());
    s.getCard();
    EXPECT_EQ(51, s.cardsRemaining());
    s.getCard();
    EXPECT_EQ(50, s.cardsRemaining());
}

TEST(ShoeTest, TestDecksRemaining)
{
    Shoe s(1, 1.0); // 1 deck, 100% penetration
    EXPECT_NEAR(1, s.decksRemaining(), 0.000001);
    for (unsigned i = 0; i < 10; ++i)
    {
        s.getCard();
    }
    EXPECT_NEAR(0.807692, s.decksRemaining(), 0.000001);
    for (unsigned i = 0; i < 3; ++i)
    {
        s.getCard();
    }
    EXPECT_NEAR(0.75, s.decksRemaining(), 0.000001);
}

TEST(ShoeTest, TestIsFinished)
{
    Shoe s(1, 0.25); // 1 deck, 60% penetration
    for (unsigned i = 0; i < 13; ++i)
    {
        s.getCard();
    }
    EXPECT_FALSE(s.isFinished());
    s.getCard();
    EXPECT_TRUE(s.isFinished());

    s = Shoe(1, 0.6); // 1 deck, 60% penetration
    for (unsigned i = 0; i < 31; ++i)
    {
        s.getCard();
    }
    EXPECT_FALSE(s.isFinished());
    s.getCard();
    EXPECT_TRUE(s.isFinished());
}

class ShoeShuffleTestClass
    : public ::testing::TestWithParam<unsigned>
{};

TEST_P(ShoeShuffleTestClass, TestShuffle)
{
    unsigned numberOfDecks = GetParam();
    Shoe s(numberOfDecks, 1); // N decks, 100% penetration
    unsigned cardsPerValue[11] = {0};  // So I don't use the zero space

    // count card per value
    unsigned short card;
    for (unsigned i = 0; i < 52 * numberOfDecks; ++i)
    {
        card = s.getCard();
        ++cardsPerValue[card];
    }
    // Check that all cards are there
    EXPECT_EQ(16 * numberOfDecks, cardsPerValue[10]);  // All 10s, Js, Qs, Ks so 4*4 = 16
    for (unsigned short i = 1; i < 10; ++i)
    {
        EXPECT_EQ(4 * numberOfDecks, cardsPerValue[i]);  // All other cards should be present 4 times per deck
    }
}

TEST_P(ShoeShuffleTestClass, TestShuffleAndRemoveCards)
{
    unsigned numberOfDecks = GetParam();
    std::vector<unsigned short> cardsToRemove = {7, 3, 3, 10, 10};
    Shoe s(numberOfDecks, 1); // N decks, 100% penetration
    s.shuffleAndRemoveCards(cardsToRemove);
    unsigned cardsPerValue[11] = {0};  // So I don't use the zero space

    // count card per value
    unsigned short card;
    for (unsigned i = 0; i < 52 * numberOfDecks - cardsToRemove.size(); ++i)
    {
        card = s.getCard();
        ++cardsPerValue[card];
    }
    // Check that all cards are there
    unsigned numberOfTensRemoved = std::count(cardsToRemove.begin(), cardsToRemove.end(), 10);
    // All 10s, Js, Qs, Ks so 4*4 = 16 per deck - the times a ten was removed
    EXPECT_EQ(16 * numberOfDecks - numberOfTensRemoved, cardsPerValue[10]);
    for (unsigned short i = 1; i < 10; ++i)
    {
        unsigned numberOfiCardRemoved = std::count(cardsToRemove.begin(), cardsToRemove.end(), i);
        // All other cards should be present 4 times per deck - the times the card was removed
        EXPECT_EQ(4 * numberOfDecks - numberOfiCardRemoved, cardsPerValue[i]);
    }
}

INSTANTIATE_TEST_SUITE_P(
    ShoeTest,
    ShoeShuffleTestClass,
    ::testing::Values(
            1, 2, 4, 6, 8
    )
);

TEST(ShoeTest, TestShuffleRandomness)
{
    unsigned LOOPS = 10000;
    unsigned DECKS = 8;
    Shoe s(DECKS, 1); // 100% penetration
    std::vector<unsigned short> previousDeckState;
    std::vector<unsigned short> newDeckState;
    previousDeckState.reserve(52*DECKS);
    newDeckState.reserve(52*DECKS);

    for (unsigned i = 0; i < 52*DECKS; ++i)
    {
        previousDeckState.push_back(s.getCard());
    }

    unsigned zeroDifferenceCounter = 0;
    for (unsigned j = 0; j < LOOPS; ++j)
    {
        s.shuffle();
        for (unsigned i = 0; i < 52*DECKS; ++i)
        {
            newDeckState.push_back(s.getCard());
            if (newDeckState[i] - previousDeckState[i] == 0)
            {
                ++zeroDifferenceCounter;
            }
        }
        previousDeckState = newDeckState;
        newDeckState.clear();
    }
    double zeroDifferenceAverage = zeroDifferenceCounter / (double)LOOPS;
    double zeroDifferenceAveragePercentage = zeroDifferenceCounter / (double)LOOPS / (52*DECKS) * 100;
    std::cout << "Zero differences average: " << zeroDifferenceAverage
              << " Percentage: " << zeroDifferenceAveragePercentage  << "%" << std::endl;
    EXPECT_NEAR(14.79, zeroDifferenceAveragePercentage, 0.11);
}

TEST(ShoeTest, TestShuffleAndRemoveCardsRandomness)
{
    unsigned LOOPS = 10000;
    unsigned DECKS = 8;
    std::vector<unsigned short> cardsToRemove{6, 6, 6};
    unsigned numberOfCards = 52*DECKS - cardsToRemove.size();
    Shoe s(DECKS, 1); // 100% penetration
    std::vector<unsigned short> previousDeckState;
    std::vector<unsigned short> newDeckState;
    previousDeckState.reserve(numberOfCards);
    newDeckState.reserve(numberOfCards);

    for (unsigned i = 0; i < numberOfCards; ++i)
    {
        previousDeckState.push_back(s.getCard());
    }

    unsigned zeroDifferenceCounter = 0;
    for (unsigned j = 0; j < LOOPS; ++j)
    {
        s.shuffleAndRemoveCards(cardsToRemove);
        for (unsigned i = 0; i < numberOfCards; ++i)
        {
            newDeckState.push_back(s.getCard());
            if (newDeckState[i] - previousDeckState[i] == 0)
            {
                ++zeroDifferenceCounter;
            }
        }
        previousDeckState = newDeckState;
        newDeckState.clear();
    }
    double zeroDifferenceAverage = zeroDifferenceCounter / (double)LOOPS;
    double zeroDifferenceAveragePercentage = zeroDifferenceCounter / (double)LOOPS / (numberOfCards) * 100;
    std::cout << "Zero differences average: " << zeroDifferenceAverage
              << " Percentage: " << zeroDifferenceAveragePercentage  << "%" << std::endl;
    EXPECT_NEAR(14.79, zeroDifferenceAveragePercentage, 0.20);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
