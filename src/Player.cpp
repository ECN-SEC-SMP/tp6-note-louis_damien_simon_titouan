#include "Player.hpp"
#include "Menu.hpp"
#include "DisplayUtils.hpp"
#include "Utils.hpp"

Player::Player(CircleColor color, std::string name)
    : color(color), name(name) {}

Player::~Player() = default;

void Player::placeCircle(GameManager &gameManager)
{
    bool placed = false;
    while (!placed)
    {
        Menu playerMenu = Menu(GAME_ASCII_BANNER + this->name + " round: (select circle size)")
                              .preventArguments();

        if (this->nbSmallCircles > 0)
            playerMenu.addOption("Small (" + std::to_string(this->nbSmallCircles) + ")");
        if (this->nbMediumCircles > 0)
            playerMenu.addOption("Medium (" + std::to_string(this->nbMediumCircles) + ")");
        if (this->nbLargeCircles > 0)
            playerMenu.addOption("Large (" + std::to_string(this->nbLargeCircles) + ")");
        int choice = playerMenu.run();

        std::cout << ANSI_BOLD "Enter frame coordinate: " ANSI_RESET << std::flush;
        std::string input;
        std::cin >> input;
        if (!std::isalpha(input.at(0)) || !std::isdigit(input.at(1)))
        {
            std::cout << ANSI_BOLD "Invalid coordinates." ANSI_RESET << std::endl;
            CONTINUE_ON_ENTER_PROMPT
            continue;
        }
        char x = input.at(0) - 'A';
        char y = input.at(1) - 1;
        if (x < 0 || x > 2 || y < 0 || y > 2)
        {
            std::cout << ANSI_BOLD "Coordinates out of range." ANSI_RESET << std::endl;
            CONTINUE_ON_ENTER_PROMPT
            continue;
        }
        CircleSize size = CircleSize(choice - 1);
        placed = gameManager.getBoard().getFrames()[x][y].tryToPlace(this->color, size);
        if (!placed)
        {
            std::cout << ANSI_BOLD "Cannot place this circle here." ANSI_RESET << std::endl;
            CONTINUE_ON_ENTER_PROMPT
            continue;
        }
    }
}

CircleColor Player::getColor() const
{
    return this->color;
}

std::string Player::getName() const
{
    return this->name;
}

std::tuple<int, int, int> Player::getInventory() const
{
    return std::make_tuple(this->nbSmallCircles, this->nbMediumCircles, this->nbLargeCircles);
}
