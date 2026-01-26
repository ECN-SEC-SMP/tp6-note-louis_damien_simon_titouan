#pragma once

#include "Menu.hpp"
#include "Otrio.hpp"

namespace MainMenu
{
    bool CB_printHelp(int pos, Menu *m);
    Menu::MenuCallback_t play_CBBuilder(Otrio &gm);
    Menu::MenuCallback_t addPlayer_CBBuilder(Otrio &gm);
    Menu::MenuCallback_t removePlayer_CBBuilder(Otrio &gm);
    Menu::MenuCallback_t settings_CBBuilder(Otrio &gm);
    Menu::MenuCallback_t stats_CBBuilder(Otrio &gm);
    bool CB_notImplementedYet(int pos, Menu *m);
} // namespace MainMenu
