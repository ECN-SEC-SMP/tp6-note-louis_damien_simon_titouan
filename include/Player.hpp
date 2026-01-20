#pragma once

#include <string>

#include "Circle.hpp"
#include "GameManager.hpp"

class Player
{
private:
    CircleColor color;
    std::string name;
    int nbSmallCircles;
    int nbMediumCircles;
    int nbLargeCircles;

public:
    Player(CircleColor color, std::string name);
    ~Player();
    void placeCircle(GameManager &gameManager);
    CircleColor getColor() const;
    std::string getName() const;
};
