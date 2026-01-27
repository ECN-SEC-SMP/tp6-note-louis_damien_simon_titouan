#pragma once

#include <vector>

#include "GameManager.hpp"
#include "Player.hpp"

#define OTRIO_MAX_PLAYER 4

enum OtrioGameMode
{
    TWO_PLAYER,
    FOUR_PLAYER
};

class Otrio
{
private:
    std::vector<Player *> players;
    std::vector<CircleColor> availableColors;
    OtrioGameMode gameMode;

public:
    Otrio();
    ~Otrio();
    /**
     * @brief Run application
     *
     * @return int error code
     */
    int run();
    /**
     * @brief Get the Player List
     *
     * @return std::vector<Player *>&
     */
    std::vector<Player *> &getPlayers();
    /**
     * @brief Add new player if possible
     * @throw std::invalid_argument
     *
     * @param[in] playerName Player Name
     */
    void addPlayer(std::string playerName);
    /**
     * @brief Remove old player if exists
     * @throw std::invalid_argument
     *
     * @param[in] playerName Player Name
     */
    void removePlayer(Player *player);
    /**
     * @brief Change new Game Mode
     *
     * @param[in] mode New Game Mode
     */
    void changeGameMode(OtrioGameMode mode);
};