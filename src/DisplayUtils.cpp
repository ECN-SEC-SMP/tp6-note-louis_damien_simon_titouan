#include <array>
#include "DisplayUtils.hpp"

#define NB_SLOTS_IN_PLAYER_INVENTORY 3

std::string Render::board(Board board)
{
    return board.toString();
}

std::string Render::playerInventory(Player *player)
{
    std::string playerStringRepr;

    PlayerInventory_t playerInventory = player->getInventory();
    CircleColor playerColor = player->getColor();

    /* To simplify slot representation, we use Frame objects and its toString() method */
    std::array<Frame, NB_SLOTS_IN_PLAYER_INVENTORY> inventorySlots;

    /* Player string representation: "PlayerName: SLOT1_REPR, SLOT2_REPR, SLOT3_REPR" */
    playerStringRepr += player->getName();
    playerStringRepr += ": ";

    /* Place circles in inventory slots */
    for (int slotIdx = 0; slotIdx < NB_SLOTS_IN_PLAYER_INVENTORY; slotIdx++)
    {
        if (playerInventory.nbSmallCircles > 0)
        {
            inventorySlots[slotIdx].tryToPlace(playerColor, SMALL);
            playerInventory.nbSmallCircles -= 1;
        }
        if (playerInventory.nbMediumCircles > 0)
        {
            inventorySlots[slotIdx].tryToPlace(playerColor, MEDIUM);
            playerInventory.nbMediumCircles -= 1;
        }
        if (playerInventory.nbLargeCircles > 0)
        {
            inventorySlots[slotIdx].tryToPlace(playerColor, LARGE);
            playerInventory.nbLargeCircles -= 1;
        }

        /* Create and add slot string representation to player string representation */
        playerStringRepr += inventorySlots[slotIdx].toString();
        playerStringRepr += " ";
    }

    return playerStringRepr;
}

std::string Render::playersInventory(std::vector<Player *> players)
{
    std::string outputString = "";

    for (Player *player : players)
    {
        /* Add string representation of the player to the output string */
        outputString += Render::playerInventory(player) + "\n";
    }

    return outputString;
}

std::string Render::playerList(std::vector<Player *> players)
{
    std::string output = ANSI_BOLD ANSI_UNDERLINE "Players:" ANSI_RESET_BOLD ANSI_RESET_UNDERLINE "\n";
    if (players.size() == 0)
    {
        output += ANSI_ITALIC "No players...\n" ANSI_RESET_ITALIC;
    }
    for (auto &&player : players)
    {
        output += " > " + player->getName() + " " + std::to_string(player->getColor()) + "\n";
    }
    output += ANSI_RESET;
    return output;
}

std::string Render::gameMode(OtrioGameMode mode)
{
    return (mode == TWO_PLAYER ? "2 players" : "4 players");
}