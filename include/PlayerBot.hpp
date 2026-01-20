#pragma once

#include <string>

#include "Player.hpp"
#include "Circle.hpp"

class GameManager;

class PlayerBot : public Player {
    public:
        void placeCircle(GameManager &gameManager) const override;

        PlayerBot(Color color,std::string name);
        ~PlayerBot();
};