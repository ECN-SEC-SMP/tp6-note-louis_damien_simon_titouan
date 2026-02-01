#include <gtest/gtest.h>
#include "GameManager.hpp"
#include "Player.hpp"
#include "Circle.hpp"
#include <array>
#include <stdexcept>

// Helper: create valid player pointers (allocated dynamically)
std::array<Player *, 4> createPlayerPointers(int count)
{
    std::array<Player *, 4> ptrs;
    CircleColor colors[] = {CircleColor::RED, CircleColor::BLUE, CircleColor::GREEN, CircleColor::ORANGE};
    for (int i = 0; i < count && i < 4; i++)
    {
        ptrs.at(i) = new Player(colors[i], "Player" + std::to_string(i + 1));
    }
    return ptrs;
}

// Helper: cleanup player pointers not managed by GameManager
void cleanupPlayers(std::array<Player *, 4> &players)
{
    for (int i = 0; i < 4; i++)
    {
        delete players[i];
        players[i] = nullptr;
    }
}

// CONSTRUCTOR TESTS

// Test: constructor with 4 players succeeds
TEST(GameManagerTest, ConstructorWithFourPlayers)
{
    std::array<Player *, 4> playerPtrs = createPlayerPointers(4);
    EXPECT_NO_THROW({
        GameManager gm(playerPtrs);
        // GameManager destructor will delete players
    });
}

// Test: constructor with wrong number throws exception
TEST(GameManagerTest, ConstructorThrowsWithWrongNumber)
{
    std::array<Player *, 4> playerPtrs = createPlayerPointers(2);
    EXPECT_THROW({ GameManager gm(playerPtrs); }, std::invalid_argument);
    // Cleanup manually since GameManager was not constructed
    cleanupPlayers(playerPtrs);
}

// Test: constructor initializes round count to 0
TEST(GameManagerTest, ConstructorInitializesRoundCount)
{
    std::array<Player *, 4> playerPtrs = createPlayerPointers(4);
    GameManager gm(playerPtrs);
    EXPECT_EQ(gm.getRoundCount(), 0);
}

// CHOOSEPLAYER ORDER TESTS

// Test: choosePlayerOrder doesn't crash
TEST(GameManagerTest, ChoosePlayerOrderRuns)
{
    std::array<Player *, 4> playerPtrs = createPlayerPointers(4);
    GameManager gm(playerPtrs);
    EXPECT_NO_THROW(gm.choosePlayerOrder());
}

// ROUND COUNT TESTS

// Test: getRoundCount returns correct value
TEST(GameManagerTest, GetRoundCount)
{
    std::array<Player *, 4> playerPtrs = createPlayerPointers(4);
    GameManager gm(playerPtrs);
    EXPECT_EQ(gm.getRoundCount(), 0);
}

// PLAYROUND TESTS

// Test: playRound returns false when no winner (simplified)
TEST(GameManagerTest, PlayRoundNoWinner)
{
    std::array<Player *, 4> playerPtrs = createPlayerPointers(4);
    GameManager gm(playerPtrs);
    // playRound should return false since checkWinConditions returns false
    bool result = gm.playRound();
    EXPECT_FALSE(result);
}

// ISLASTROUND TESTS

// Test: isLastRound returns false when round < nbRound
TEST(GameManagerTest, IsLastRoundReturnsFalse)
{
    std::array<Player *, 4> playerPtrs = createPlayerPointers(4);
    GameManager gm(playerPtrs);
    gm.setRoundCount(10);
    EXPECT_FALSE(gm.isLastRound());
}

// Test: isLastRound returns true when round == nbRound
TEST(GameManagerTest, IsLastRoundReturnsTrue)
{
    std::array<Player *, 4> playerPtrs = createPlayerPointers(4);
    GameManager gm(playerPtrs);
    gm.setRoundCount(NBROUND);
    EXPECT_TRUE(gm.isLastRound());
}

// Test: isLastRound throws exception when round > nbRound
TEST(GameManagerTest, IsLastRoundThrowsException)
{
    std::array<Player *, 4> playerPtrs = createPlayerPointers(4);
    GameManager gm(playerPtrs);
    gm.setRoundCount(NBROUND + 1);
    EXPECT_THROW(gm.isLastRound(), std::range_error);
}

// STARTGAME TESTS

// Test: startGame initializes round count to 0 and calls choosePlayerOrder
TEST(GameManagerTest, StartGameInitializes)
{
    std::array<Player *, 4> playerPtrs = createPlayerPointers(4);
    GameManager gm(playerPtrs);
    gm.setRoundCount(10);
    gm.startGame();
    EXPECT_EQ(gm.getRoundCount(), 0);
}
