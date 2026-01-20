#pragma once

#include "Board.hpp"
#include "Player.hpp"


class GameManager
    {
    private :
        Board board;
        std::array<Player, 4>& players;
        int roundCount;

    public :
        // Constructor and Destructor
        GameManager(std::array<Player, 4>& players);
        ~GameManager();

        // Check Win
        bool checkWinConditions(const Frame frame_played);
        bool checkWinCondition1(const Frame frame_played);
        bool checkWinCondition2(const Frame frame_played);
        bool checkWinCondition3(const Frame frame_played);
        
        // Game turn management
        void startGame();
        void playRound();

        // Tool function
        bool isLastRound();
    };
