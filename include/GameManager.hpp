#pragma once

#include "Board.hpp"
#include "Player.hpp"
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <random>
#include <iostream>
#include <array>

#define NBROUND 27
class GameManager
{
protected:
    Board board;
    std::array<Player *, 4> players;
    int roundCount;
    Player *winnerPlayer;

public:
    // Check Win
    bool checkWinConditions(const int x, const int y, const CircleColor targetColor) const;
    bool checkWinCondition1(const Frame frame_played) const;
    bool checkWinCondition2(const Frame frame_played) const;
    bool checkWinCondition3(const Frame frame_played) const;

    // Game turn management
    void manageGame();
    void manageRounds();
    bool playRound();

    // Tool function
    bool isLastRound() const;
    void choosePlayerOrder();
    // Constructor and Destructor
    GameManager(std::array<Player *, 4> &newPlayers);
    ~GameManager();

    // Getters and setters
    int getRoundCount() const;
    void setRoundCount(int roundCount);
    void incrementRoundCount(int n);
    void setWinner(Player *winner);

    // Game turn management
    void startGame();

    // Getters
    Board &getBoard();
    Player *getWinner();
};
