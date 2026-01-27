#pragma once

#include <string>

#include "Player.hpp"
#include "Circle.hpp"

class GameManager;

class PlayerBot : public Player
{
public:
    PlayerBot(CircleColor color, std::string name);
    ~PlayerBot();

    std::pair<int, int> placeCircle(GameManager &gameManager) override;
};