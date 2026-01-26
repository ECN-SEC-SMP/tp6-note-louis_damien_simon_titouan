#include <algorithm>
#include <stdexcept>

#include "Otrio.hpp"
#include "Menu.hpp"
#include "DisplayUtils.hpp"
#include "MainMenuCallbacks.hpp"

Otrio::Otrio()
{
    this->availableColors.push_back(CircleColor::RED);
    this->availableColors.push_back(CircleColor::GREEN);
    this->availableColors.push_back(CircleColor::BLUE);
    this->availableColors.push_back(CircleColor::ORANGE);
}

Otrio::~Otrio() = default;

int Otrio::run()
{
    bool running = true;
    Menu mainMenu = Menu(GAME_ASCII_BANNER ANSI_BOLD "Main Menu" ANSI_RESET, 0)
                        .addOption("Play", MainMenu::play_CBBuilder(*this))
                        .addOption("Add Player", MainMenu::addPlayer_CBBuilder(*this))
                        .addOption("Remove Player", MainMenu::removePlayer_CBBuilder(*this))
                        //  .addOption("Stats", MainMenu::stats_CBBuilder(gm))
                        //  .addOption("Settings", MainMenu::settings_CBBuilder(gm))
                        .addOption("Help", MainMenu::CB_printHelp)
                        .addOption("Exit.", [&](int pos, Menu *m)
                                   { running = false; return false; })
                        .preventArguments();

    int pos = 1;
    while (running)
    {
        mainMenu.setTitle(GAME_ASCII_BANNER ANSI_BOLD "Main Menu\n\n" ANSI_RESET + DisplayUtils::getStringFromPlayerList(this->players)); // Actualize title
        mainMenu.setOptionPos(pos);                                                                                                       // Keep last position
        pos = mainMenu.run();
    }
    return 0;
}

std::vector<Player *> &Otrio::getPlayers()
{
    return this->players;
}

void Otrio::addPlayer(std::string playerName)
{
    if (this->players.size() >= OTRIO_MAX_PLAYER)
        throw std::invalid_argument("Max player count reached.");
    if (this->availableColors.empty())
        throw std::invalid_argument("Otrio::availableColors empty.");
    this->players.push_back(new Player(this->availableColors.back(), playerName));
    this->availableColors.pop_back();
}

void Otrio::removePlayer(Player *player)
{
    if (std::find(this->players.begin(), this->players.end(), player) == this->players.end())
        throw std::invalid_argument("Player not exists");

    this->availableColors.push_back(player->getColor());
    this->players.erase(std::find(this->players.begin(), this->players.end(), player));
}
