#include <iostream>

#include "MainMenuCallbacks.hpp"
#include "DisplayUtils.hpp"
#include "Utils.hpp"

////////////////////////////////////////////////////////////////////////////////
//                                  Macros                                    //
////////////////////////////////////////////////////////////////////////////////
#define CONTINUE_ON_ENTER_PROMPT                              \
    std::cin.clear();                                         \
    std::cout << "Press [ENTER] to continue..." << std::endl; \
    std::cin.ignore(100, '\n');
#define key(str) ANSI_BLUE str ANSI_RESET
#define red_word(str) ANSI_RED str ANSI_RESET

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

Menu::MenuCallback_t MainMenu::play_CBBuilder(Otrio &gm)
{
    auto lambda_cb = [&](int pos, Menu *m)
    {
        // if (gm.getPlayers().size() == 0)
        // {
        //     std::cout << "No players added!" << std::endl;
        //     CONTINUE_ON_ENTER_PROMPT
        // }
        // else
        // {
        //     gm.setupRound();
        //     gm.processPredictionsInputs();
        //     gm.sortPlayersByPredictions();
        //     int player_index = 0;
        //     bool player_won = false;
        //     do
        //     {
        //         if ((player_won = gm.playRound(player_index)) == true)
        //             std::cout << ANSI_GREEN ANSI_BOLD "You WON!!" ANSI_RESET << std::endl;
        //         else
        //         {
        //             std::cout << ANSI_RED ANSI_BOLD "You Lose!" ANSI_RESET << std::endl;
        //             player_index++;
        //         }
        //         CONTINUE_ON_ENTER_PROMPT
        //     } while (player_won == false && player_index < (int)gm.getPlayers().size());
        //     Menu::clear();
        //     std::cout << gm.displayBoard() << gm.displayRoundResults() << std::endl;
        //     CONTINUE_ON_ENTER_PROMPT
        // }

        return false;
    };
    return lambda_cb;
}

Menu::MenuCallback_t MainMenu::addPlayer_CBBuilder(Otrio &gm)
{
    auto lambda_cb = [&](int pos, Menu *m)
    {
        if (gm.getPlayers().size() == OTRIO_MAX_PLAYER)
        {
            Menu player_menu(GAME_ASCII_BANNER ANSI_BOLD "\nMax player count reachded.\n" ANSI_RESET, 0);
            player_menu.addOption("Back");
            player_menu.run();
            return false;
        }

        Menu player_menu(GAME_ASCII_BANNER ANSI_BOLD "Add Player\n" ANSI_ITALIC "(Set player name on first option)\n" ANSI_RESET, 0);
        // player_menu.setColorSelection(gm.getBoardTheme().menu_selection_color);
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
            for (auto &&player : gm.getPlayers())
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
                gm.addPlayer(player_name);
            }
        }

        return false;
    };
    return lambda_cb;
}

Menu::MenuCallback_t MainMenu::removePlayer_CBBuilder(Otrio &gm)
{
    auto lambda_cb = [&](int pos, Menu *m)
    {
        Menu player_menu(GAME_ASCII_BANNER ANSI_BOLD "Remove Player\n" ANSI_RESET, 0);
        // player_menu.setColorSelection(gm.getBoardTheme().menu_selection_color);
        player_menu.preventArguments();
        for (auto &&player : gm.getPlayers())
        {
            player_menu.addOption(player->getName());
        }
        player_menu.addOption("Cancel.");
        int player_pos = player_menu.run();
        if (player_pos > 0 && player_pos <= (int)gm.getPlayers().size())
        {
            gm.removePlayer(gm.getPlayers().at(player_pos - 1));
        }
        return false;
    };
    return lambda_cb;
}

Menu::MenuCallback_t MainMenu::stats_CBBuilder(Otrio &gm)
{
    auto lambda_cb = [&](int pos, Menu *m)
    {
        // Menu stats_menu = Menu(GAME_ASCII_BANNER + gm.displayScoreboard()).addOption("Reset all").addOption("Exit.").preventArguments();
        // int index = stats_menu.run();
        // if (index == 1)
        // {
        //     Menu confirmation_menu = Menu(GAME_ASCII_BANNER + gm.displayScoreboard() + "\nAre you sure?").addOption("yes").addOption("no").preventArguments();
        //     int yn = confirmation_menu.run();
        //     if (yn == 1)
        //     {
        //         for (auto &&p : gm.getPlayers())
        //         {
        //             p->reset();
        //         }
        //     }
        // }

        return false;
    };
    return lambda_cb;
}

// Menu::MenuCallback_t MainMenu::function_CBBuilder(Otrio &gm)
// {
//     auto lambda_cb = [&](int pos, Menu *m)
//     {
//         // some code

//         return false;
//     };
//     return lambda_cb;
// }