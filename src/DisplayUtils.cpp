#include "DisplayUtils.hpp"

std::string DisplayUtils::getPlayerList(std::vector<Player *> players)
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