#include "Player.hpp"
#include "Menu.hpp"
#include "DisplayUtils.hpp"
#include "Utils.hpp"

Player::Player(CircleColor color, std::string name)
    : color(color), name(name)
{
    this->inventory.nbSmallCircles = 3;
    this->inventory.nbMediumCircles = 3;
    this->inventory.nbLargeCircles = 3;
}

Player::~Player() = default;

std::pair<int, int> Player::placeCircle(GameManager &gameManager)
{
    bool placed = false;
    int x = -1, y = -1;
    while (!placed)
    {
        // Setup Menu
        Menu playerMenu = Menu(GAME_ASCII_BANNER + gameManager.getBoard().toString() + "\n\n" ANSI_BOLD + this->name + " round: " ANSI_RESET "(select circle size)\n")
                              .preventArguments()
                              .addOption("Small (" + std::to_string(this->inventory.nbSmallCircles) + ")")
                              .addOption("Medium (" + std::to_string(this->inventory.nbMediumCircles) + ")")
                              .addOption("Large (" + std::to_string(this->inventory.nbLargeCircles) + ")");

        // Get circle size choice
        int choice = playerMenu.run();

        // Check circle availability
        if (choice == 1 && this->inventory.nbSmallCircles == 0)
        {
            std::cout << ANSI_BOLD "No more SMALL circle." ANSI_RESET << std::endl;
            CONTINUE_ON_ENTER_PROMPT
            continue;
        }
        if (choice == 2 && this->inventory.nbMediumCircles == 0)
        {
            std::cout << ANSI_BOLD "No more MEDIUM circle." ANSI_RESET << std::endl;
            CONTINUE_ON_ENTER_PROMPT
            continue;
        }
        if (choice == 3 && this->inventory.nbLargeCircles == 0)
        {
            std::cout << ANSI_BOLD "No more LARGE circle." ANSI_RESET << std::endl;
            CONTINUE_ON_ENTER_PROMPT
            continue;
        }

        // Ask coordinates
        std::cout << ANSI_BOLD "Enter frame coordinate: " ANSI_RESET << std::flush;
        std::string input;
        std::cin >> input;

        // Check coordinates validity
        if (input.size() < 2 || !std::isalpha(input.at(0)) || !std::isdigit(input.at(1)))
        {
            std::cout << ANSI_BOLD "Invalid coordinates." ANSI_RESET << std::endl;
            CONTINUE_ON_ENTER_PROMPT
            continue;
        }
        std::cin.ignore(100, '\n'); // Wait until ENTER

        // Prepare and check real coordinates
        x = input.at(0) - 'A';
        y = input.at(1) - '0' - 1;
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

        // Decrement inventory
        switch (size)
        {
        case SMALL:
            this->inventory.nbSmallCircles--;
            break;
        case MEDIUM:
            this->inventory.nbMediumCircles--;
            break;
        case LARGE:
            this->inventory.nbLargeCircles--;
            break;
        default:
            break;
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
