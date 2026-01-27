#pragma once

#include "Board.hpp"
#include "Player.hpp"

class GameManager
{
private:
    Board board;
    std::array<Player *, 4> players;
    int roundCount;

private:
    // Check Win
    bool checkWinConditions(const Frame frame_played) const;
    bool checkWinCondition1(const Frame frame_played) const;
    bool checkWinCondition2(const Frame frame_played) const;
    bool checkWinCondition3(const Frame frame_played) const;

    // Game turn management
    void playRound();

    // Tool function
    bool isLastRound() const;

public:
    // Constructor and Destructor
    GameManager(std::array<Player *, 4> players);
    ~GameManager();

    // Game turn management
    void startGame();

    // Getters
    Board &getBoard();
    Player *getWinner();
};
