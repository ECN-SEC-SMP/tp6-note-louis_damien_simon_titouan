#pragma once

#include <string>
#include <tuple>

#include "Circle.hpp"

// Avoid circular include
class GameManager;

class Player
{
private:
    CircleColor color;
    std::string name;
    int nbSmallCircles;
    int nbMediumCircles;
    int nbLargeCircles;

public:
    /**
     * @brief Construct a new Player object
     *
     * @param[in] color Color of the player
     * @param[in] name Name of the player
     */
    Player(CircleColor color, std::string name);
    ~Player();
    /**
     * @brief Prompt player and place his circle
     *
     * @param[inout] gameManager Reference of parent game manager instance
     */
    void placeCircle(GameManager &gameManager);
    /**
     * @brief Get the Player Color
     *
     * @return CircleColor Color of the player
     */
    CircleColor getColor() const;
    /**
     * @brief Get the Player Name
     *
     * @return std::string Name of the player
     */
    std::string getName() const;
    /**
     * @brief Get the Player Inventory
     * @details nbSmallCircles, nbMediumCircles, nbLargeCircles
     *
     * @return std::tuple<int, int, int>
     */
    std::tuple<int, int, int> getInventory() const;
};
