#include "Player.hpp"

Player::Player(CircleColor color, std::string name)
    : color(color), name(name) {}

Player::~Player() = default;

void Player::placeCircle(GameManager &gameManager)
{
    // #TODO
}

CircleColor Player::getColor() const
{
    return this->color;
}

std::string Player::getName() const
{
    return this->name;
}

std::tuple<int, int, int> Player::getIventory() const
{
    return std::make_tuple(this->nbSmallCircles, this->nbMediumCircles, this->nbLargeCircles);
}
