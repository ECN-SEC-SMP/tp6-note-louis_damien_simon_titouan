#pragma once

#include <vector>

#include "GameManager.hpp"
#include "Player.hpp"

class Otrio
{
private:
    GameManager gameManager;
    std::vector<Player> players;

public:
    Otrio();
    ~Otrio();
    int run();
};