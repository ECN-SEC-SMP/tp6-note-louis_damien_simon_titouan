#pragma once

#include "Board.hpp"
#include "Player.hpp"
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <random>
#include <iostream>
#include <array>

#define nbRound 27
class GameManager
{
protected :  
    Board board;
    std::array<Player *, 4> players;
    int roundCount;
    
    
    public:
    // Check Win
    bool checkWinConditions() const;
    bool checkWinCondition1(const Frame frame_played) const;
    bool checkWinCondition2(const Frame frame_played) const;
    bool checkWinCondition3(const Frame frame_played) const;

    // Game turn management
    void playRound();

    // Tool function
    bool isLastRound() const;
    void choosePlayerOrder();
    // Constructor and Destructor
    GameManager(std::vector<Player*> &newPlayers);
    ~GameManager();

    //Getters and setters
    int getRoundCount() const;
    void setRoundCount(int roundCount);
    void incrementRoundCount(int n);
    
    // Game turn management
    void startGame();
};
