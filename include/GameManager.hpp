#pragma once

#include <random>    
#include <algorithm> 
#include <iostream>  
#include "Board.hpp"
#include <vector>
#include <string>
#include <array>


class Player; 
enum CircleColor; 


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
    bool checkWinConditions(const int x, const int y, const CircleColor targetColor, const Board* sourceBoard) const;
    bool checkWinCondition1(const int x, const int y, const CircleColor targetColor, const Board* sourceBoard) const;
    bool checkWinCondition2(const int x, const int y, const CircleColor targetColor, const Board* sourceBoard) const;
    bool checkWinCondition3(const int x, const int y, const CircleColor targetColor, const Board* sourceBoard) const;

    // Game turn management
    void manageGame();
    void manageRounds();
    bool playRound();

    // Tool function
    bool isLastRound() const;
    void choosePlayerOrder();
    std::string renderBoard();

    // Constructor and Destructor
    GameManager(std::array<Player *, 4> &newPlayers);
    ~GameManager();

    // Getters and setters
    Board &getBoard();
    int getRoundCount() const;
    void setRoundCount(int roundCount);
    void incrementRoundCount(int n);
    Player *getWinner();
    void setWinner(Player *winner);
    std::array<Player *, 4> getPlayers() const;

    // Game turn management
    void startGame();
};
