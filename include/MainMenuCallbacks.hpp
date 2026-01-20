#pragma once

#include "ANSI.hpp"
#include "Menu.hpp"
#include "Otrio.hpp"

/* some stuff */
#define CONTINUE_ON_ENTER_PROMPT                              \
    std::cin.clear();                                         \
    std::cout << "Press [ENTER] to continue..." << std::endl; \
    std::cin.ignore(100, '\n');
#define key(str) ANSI_BLUE str ANSI_RESET
#define red_word(str) ANSI_RED str ANSI_RESET

namespace SettingsMenu
{
    Menu::MenuCallback_t menuSelectionColor_CBBuilder(Otrio &gm);
    Menu::MenuCallback_t menuRobotSelectedColor_CBBuilder(Otrio &gm);
    Menu::MenuCallback_t robotReplacedEachRound_CBBuilder(Otrio &gm);
    Menu::MenuCallback_t backgroundColor_CBBuilder(Otrio &gm);
    Menu::MenuCallback_t wallsColor_CBBuilder(Otrio &gm);
    Menu::MenuCallback_t gridColor_CBBuilder(Otrio &gm);
    Menu::MenuCallback_t wallsStyle_CBBuilder(Otrio &gm);
    Menu::MenuCallback_t colorTheme_CBBuilder(Otrio &gm);
} // namespace SettingsMenu

namespace MenuUtils
{
    std::string getColorWithMenu(std::string title, std::string selectionColor = ANSI_GREEN);
    std::string getBGColorWithMenu(std::string title, std::string selectionColor = ANSI_GREEN);
} // namespace MenuUtils

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
