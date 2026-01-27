#include "Player.hpp"
#include "Menu.hpp"
#include "DisplayUtils.hpp"
#include "Utils.hpp"

Player::Player(CircleColor color, std::string name)
    : color(color), name(name)
{
}

Player::~Player() = default;

std::pair<int, int> Player::placeCircle(GameManager &gameManager)
{
    bool placed = false;
    int x = -1, y = -1;
    while (!placed)
    {
        // Setup Menu
        Menu playerMenu(GAME_ASCII_BANNER + this->name + " round: (select circle size)");
        playerMenu.preventArguments();

        // Add available options
        if (this->inventory.nbSmallCircles > 0)
            playerMenu.addOption("Small (" + std::to_string(this->inventory.nbSmallCircles) + ")");
        if (this->inventory.nbMediumCircles > 0)
            playerMenu.addOption("Medium (" + std::to_string(this->inventory.nbMediumCircles) + ")");
        if (this->inventory.nbLargeCircles > 0)
            playerMenu.addOption("Large (" + std::to_string(this->inventory.nbLargeCircles) + ")");

        // Get circle size choice
        int choice = playerMenu.run();

        // Ask coordinates
        std::cout << ANSI_BOLD "Enter frame coordinate: " ANSI_RESET << std::flush;
        std::string input;
        std::cin >> input;

        // Check coordinates validity
        if (!std::isalpha(input.at(0)) || !std::isdigit(input.at(1)))
        {
            std::cout << ANSI_BOLD "Invalid coordinates." ANSI_RESET << std::endl;
            CONTINUE_ON_ENTER_PROMPT
            continue;
        }

        // Prepare and check real coordinates
        x = input.at(0) - 'A';
        y = input.at(1) - 1;
        if (x < 0 || x > 2 || y < 0 || y > 2)
        {
            std::cout << ANSI_BOLD "Coordinates out of range." ANSI_RESET << std::endl;
            CONTINUE_ON_ENTER_PROMPT
            continue;
        }

        // Try to place circle
        CircleSize size = CircleSize(choice - 1);
        placed = gameManager.getBoard().getFrames()[x][y].tryToPlace(this->color, size);
        if (!placed)
        {
            std::cout << ANSI_BOLD "Cannot place this circle here." ANSI_RESET << std::endl;
            CONTINUE_ON_ENTER_PROMPT
            continue;
        }
    }
    // Return coordinates of the placed circle
    return std::make_pair(x, y);
}

CircleColor Player::getColor() const
{
    return this->color;
}

std::string Player::getName() const
{
    return this->name;
}

PlayerInventory_t Player::getInventory() const
{
    return this->inventory;
}
