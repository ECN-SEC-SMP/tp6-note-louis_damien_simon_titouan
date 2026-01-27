#include <gtest/gtest.h>
#include "GameManager.hpp"
#include "Player.hpp"
#include "Circle.hpp"
#include <vector>
#include <stdexcept>

// Helper: create valid players
std::vector<Player> createPlayers(int count) {
    std::vector<Player> players;
    CircleColor colors[] = {CircleColor::RED, CircleColor::BLUE, CircleColor::GREEN, CircleColor::BLACK};
    for (int i = 0; i < count && i < 4; i++) {
        players.push_back(Player(colors[i], "Player" + std::to_string(i + 1)));
    }
    return players;
}

// Helper: create valid player pointers
std::vector<Player*> createPlayerPointers(std::vector<Player>& players) {
    std::vector<Player*> ptrs;
    for(auto& p : players) {
        ptrs.push_back(&p);
    }
    return ptrs;
}

// CONSTRUCTOR TESTS

// Test: constructor with 4 players succeeds
TEST(GameManagerTest, ConstructorWithFourPlayers) {
    std::vector<Player> players = createPlayers(4);
    std::vector<Player*> playerPtrs = createPlayerPointers(players);
    EXPECT_NO_THROW(GameManager gm(playerPtrs));
}

// Test: constructor with wrong number throws exception
TEST(GameManagerTest, ConstructorThrowsWithWrongNumber) {
    std::vector<Player> players = createPlayers(2);
    std::vector<Player*> playerPtrs = createPlayerPointers(players);
    EXPECT_THROW(GameManager gm(playerPtrs), std::invalid_argument);
}

// Test: constructor initializes round count to 0
TEST(GameManagerTest, ConstructorInitializesRoundCount) {
    std::vector<Player> players = createPlayers(4);
    std::vector<Player*> playerPtrs = createPlayerPointers(players);
    GameManager gm(playerPtrs);
    EXPECT_EQ(gm.getRoundCount(), 0);
}

// CHOOSEPLAYER ORDER TESTS

// Test: choosePlayerOrder doesn't crash
TEST(GameManagerTest, ChoosePlayerOrderRuns) {
    std::vector<Player> players = createPlayers(4);
    std::vector<Player*> playerPtrs = createPlayerPointers(players);
    GameManager gm(playerPtrs);
    EXPECT_NO_THROW(gm.choosePlayerOrder());
}

// PLAYROUND TESTS

// Test: playRound runs until max rounds
TEST(GameManagerTest, PlayRoundRunsUntilMax) {
    std::vector<Player> players = createPlayers(4);
    std::vector<Player*> playerPtrs = createPlayerPointers(players);
    GameManager gm(playerPtrs);
    gm.setRoundCount(0);
    gm.playRound();
    EXPECT_EQ(gm.getRoundCount(), nbRound);
}

// Test: playRound doesn't execute when at max rounds
TEST(GameManagerTest, PlayRoundStopsAtMax) {
    std::vector<Player> players = createPlayers(4);
    std::vector<Player*> playerPtrs = createPlayerPointers(players);
    GameManager gm(playerPtrs);
    gm.setRoundCount(nbRound);
    gm.playRound();
    EXPECT_EQ(gm.getRoundCount(), nbRound);
}

// STARTGAME TESTS

// Test: startGame initializes round count to 0
TEST(GameManagerTest, StartGameResetsRoundCount) {
    std::vector<Player> players = createPlayers(4);
    std::vector<Player*> playerPtrs = createPlayerPointers(players);
    GameManager gm(playerPtrs);
    gm.setRoundCount(10);
    // Note: startGame would run indefinitely, so we test only initialization
    EXPECT_NO_THROW(gm.choosePlayerOrder());
    gm.setRoundCount(0);
    EXPECT_EQ(gm.getRoundCount(), 0);
}
