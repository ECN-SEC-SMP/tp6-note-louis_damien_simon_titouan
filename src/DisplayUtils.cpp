#include "DisplayUtils.hpp"

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