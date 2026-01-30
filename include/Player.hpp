#pragma once

#include <string>
#include <tuple>

#include "Circle.hpp"

// Avoid circular include
class GameManager;

typedef struct PlayerInventory_t
{
    int nbSmallCircles;
    int nbMediumCircles;
    int nbLargeCircles;
} PlayerInventory_t;

class Player
{
private:
    CircleColor color;
    std::string name;

protected:

    PlayerInventory_t inventory;

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
     *
     * @return std::pair<int, int> Coordinates of the placed circle
     */
    virtual std::pair<int, int> placeCircle(GameManager &gameManager);
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
     *
     * @return PlayerInventory_t
     */
    PlayerInventory_t getInventory() const;
};
