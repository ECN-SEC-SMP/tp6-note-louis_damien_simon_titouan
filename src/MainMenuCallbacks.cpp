#include <iostream>

#include "MainMenuCallbacks.hpp"
#include "DisplayUtils.hpp"
#include "Utils.hpp"

////////////////////////////////////////////////////////////////////////////////
//                            MainMenu Functions                              //
////////////////////////////////////////////////////////////////////////////////
bool MainMenu::CB_notImplementedYet(int pos, Menu *m)
{
    Menu::clear();
    std::cout << GAME_ASCII_BANNER << std::endl;
    std::cout << "Not implemented yet! " << std::endl;
    CONTINUE_ON_ENTER_PROMPT

    return false;
}

bool MainMenu::CB_printHelp(int pos, Menu *m)
{
    Menu::clear();

    std::cout << GAME_ASCII_BANNER;
    std::cout << ANSI_BOLD "Help Page" ANSI_RESET_BOLD << std::endl
              << std::endl;
    std::cout << "NOT IMPLEMENTED YET" << std::endl;
    std::cout << std::endl;
    CONTINUE_ON_ENTER_PROMPT

    return true;
}

Menu::MenuCallback_t MainMenu::play_CBBuilder(Otrio &otrio)
{
    auto lambda_cb = [&](int pos, Menu *m)
    {
        return false;
    };
    return lambda_cb;
}

Menu::MenuCallback_t MainMenu::addPlayer_CBBuilder(Otrio &otrio)
{
    auto lambda_cb = [&](int pos, Menu *m)
    {
        if (otrio.getPlayers().size() == OTRIO_MAX_PLAYER)
        {
            Menu player_menu(GAME_ASCII_BANNER ANSI_BOLD "\nMax player count reachded.\n" ANSI_RESET, 0);
            player_menu.addOption("Back");
            player_menu.run();
            return false;
        }

        Menu player_menu(GAME_ASCII_BANNER ANSI_BOLD "Add Player\n" ANSI_ITALIC "(Set player name on first option)\n" ANSI_RESET, 0);
        // player_menu.setColorSelection(otrio.getBoardTheme().menu_selection_color);
        player_menu.addOption("Player name: ").addOption("Cancel.");
        std::string player_name;
        int sel_pos;
        do
        {
            sel_pos = player_menu.run();
            if (sel_pos != 1)
                continue;
            player_name = player_menu.getOptionsArgs()[0];
            player_name = Utils::reduce(player_name, "_");
        } while (player_name.empty() && sel_pos == 1);

        if (sel_pos == 1)
        {
            bool found = false;
            for (auto &&player : otrio.getPlayers())
            {
                if (player->getName() == player_name)
                {
                    found = true;
                    break;
                }
            }
            if (found) // Player name exists
            {
                std::cout << "This player name already exists! Retry." << std::endl;
                CONTINUE_ON_ENTER_PROMPT
            }
            else
            {
                otrio.addPlayer(player_name);
            }
        }

        return false;
    };
    return lambda_cb;
}

Menu::MenuCallback_t MainMenu::removePlayer_CBBuilder(Otrio &otrio)
{
    auto lambda_cb = [&](int pos, Menu *m)
    {
        Menu player_menu(GAME_ASCII_BANNER ANSI_BOLD "Remove Player\n" ANSI_RESET, 0);
        // player_menu.setColorSelection(otrio.getBoardTheme().menu_selection_color);
        player_menu.preventArguments();
        for (auto &&player : otrio.getPlayers())
        {
            player_menu.addOption(player->getName());
        }
        player_menu.addOption("Cancel.");
        int player_pos = player_menu.run();
        if (player_pos > 0 && player_pos <= (int)otrio.getPlayers().size())
        {
            otrio.removePlayer(otrio.getPlayers().at(player_pos - 1));
        }
        return false;
    };
    return lambda_cb;
}

Menu::MenuCallback_t MainMenu::gameMode_CBBuilder(Otrio &otrio)
{
    auto lambda_cb = [&](int pos, Menu *m)
    {
        Menu gameModeMenu = Menu(GAME_ASCII_BANNER "Choose game mode").addOption("Two player mode").addOption("Four player mode").addOption("Cancel.").preventArguments();
        int index = gameModeMenu.run();

        if (index == 1)
        {
            otrio.changeGameMode(TWO_PLAYER);
        }
        else if (index == 2)
        {
            otrio.changeGameMode(FOUR_PLAYER);
        }

        return false;
    };
    return lambda_cb;
}

// Menu::MenuCallback_t MainMenu::function_CBBuilder(Otrio &otrio)
// {
//     auto lambda_cb = [&](int pos, Menu *m)
//     {
//         // some code

//         return false;
//     };
//     return lambda_cb;
// }