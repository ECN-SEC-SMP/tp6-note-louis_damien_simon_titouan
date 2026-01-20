#pragma once

#include <vector>

#include "GameManager.hpp"
#include "Player.hpp"

#define OTRIO_MAX_PLAYER 4

class Otrio
{
private:
    std::vector<Player *> players;
    std::vector<CircleColor> freeColors;

public:
    Otrio();
    ~Otrio();
    int run();
    std::vector<Player *> &getPlayers();
    void addPlayer(std::string player_name);
    void removePlayer(Player *player);
};