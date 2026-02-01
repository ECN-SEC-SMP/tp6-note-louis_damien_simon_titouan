#include <iostream>

#include "MainMenuCallbacks.hpp"
#include "DisplayUtils.hpp"
#include "Utils.hpp"
#include "PlayerBot.hpp"

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

Menu::MenuCallback_t MainMenu::play_CBBuilder(Otrio &otrio)
{
    auto lambda_cb = [&](int pos, Menu *m)
    {
        /// Check if there is at least one player
        if (otrio.getPlayers().empty())
        {
            std::cout << ANSI_BOLD "There is no player..." ANSI_RESET << std::endl;
            CONTINUE_ON_ENTER_PROMPT
            return false;
        }

        /// Prepare players
        std::array<Player *, 4> real_players;
        if (otrio.getGameMode() == FOUR_PLAYER)
        {
            int i = 0;
            // Add all available players
            for (auto &&p : otrio.getPlayers())
            {
                real_players[i] = new Player(p->getColor(), p->getName());
                i++;
            }
            // If players list is not full, add bots to complete
            if (i < 4)
            {
                auto availableColor = otrio.getAvailableCircleColor();
                for (int j = i; j < 4; j++)
                {
                    real_players[j] = new PlayerBot(availableColor.back(), "Bot " + std::to_string(j));
                    availableColor.pop_back();
                }
            }
        }
        else if (otrio.getGameMode() == TWO_PLAYER)
        {
            int i = 0;
            auto availableColor = otrio.getAvailableCircleColor();
            // Add all available players
            for (auto &&p : otrio.getPlayers())
            {
                real_players[i] = new Player(p->getColor(), p->getName());
                real_players[i + 2] = new Player(availableColor.back(), p->getName());
                availableColor.pop_back();
                i++;
            }
            // If players list is not full, add bots to complete
            if (i < 2)
            {
                real_players[1] = new PlayerBot(availableColor.back(), "Bot");
                availableColor.pop_back();
                real_players[3] = new PlayerBot(availableColor.back(), "Bot");
                availableColor.pop_back();
            }
        }

        /// Setup GameManager
        GameManager gameManager(real_players);

        /// Launch Game
        gameManager.startGame();

        /// Display Winner
        Player *winner = gameManager.getWinner();
        if (winner)
        {
            Menu::clear();
            std::cout << GAME_ASCII_BANNER
                      << gameManager.renderBoard()
                      << std::endl
                      << ANSI_BOLD ANSI_UNDERLINE + winner->getName() + " won the game!" ANSI_RESET << std::endl
                      << std::endl;
        }
        else
        {
            Menu::clear();
            std::cout << GAME_ASCII_BANNER
                      << gameManager.renderBoard()
                      << std::endl
                      << ANSI_BOLD ANSI_UNDERLINE "GAME OVER!" ANSI_RESET << std::endl
                      << std::endl;
        }
        CONTINUE_ON_ENTER_PROMPT

        return false;
    };
    return lambda_cb;
}

Menu::MenuCallback_t MainMenu::addPlayer_CBBuilder(Otrio &otrio)
{
    auto lambda_cb = [&](int pos, Menu *m)
    {
        /// Check max players
        if (otrio.getPlayers().size() == OTRIO_MAX_PLAYER)
        {
            Menu player_menu(GAME_ASCII_BANNER ANSI_BOLD "\nMax player count reachded.\n" ANSI_RESET, 0);
            player_menu.addOption("Back");
            player_menu.run();
            return false;
        }

        /// Prepare Menu
        Menu player_menu(GAME_ASCII_BANNER ANSI_BOLD "Add Player\n" ANSI_ITALIC "(Set player name on first option)\n" ANSI_RESET, 0);
        // player_menu.setColorSelection(otrio.getBoardTheme().menu_selection_color);
        player_menu.addOption("Player name: ").addOption("Cancel.");

        /// Get and prepare player name
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

        /// Try to add new player
        if (sel_pos == 1)
        {
            // Check if player exists
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

bool MainMenu::CB_printHelp(int pos, Menu *m)
{
    Menu::clear();

    std::cout << GAME_ASCII_BANNER;
    std::cout << ANSI_BOLD "Help Page" ANSI_RESET_BOLD << std::endl
              << std::endl;

    std::cout << ANSI_UNDERLINE "Rules:" ANSI_RESET_UNDERLINE << std::endl;
    std::cout << " 1. The goal of OTRIO is to align or stack three circles" << std::endl;
    std::cout << "    of your own color." << std::endl;
    std::cout << " 2. Each player has " ANSI_UNDERLINE "9 circles" ANSI_RESET_UNDERLINE ":" << std::endl;
    std::cout << "    3 Small, 3 Medium, and 3 Large." << std::endl;
    std::cout << " 3. The board is a 3x3 grid. Each cell can contain up to" << std::endl;
    std::cout << "    three circles (Small inside Medium inside Large)." << std::endl;
    std::cout << " 4. Players take turns placing " ANSI_UNDERLINE "one circle" ANSI_RESET_UNDERLINE " of their color" << std::endl;
    std::cout << "    and chosen size on a valid position." << std::endl;
    std::cout << " 5. A move is valid only if the selected size is still available" << std::endl;
    std::cout << "    and the position for that size is free." << std::endl;

    std::cout << std::endl;
    std::cout << ANSI_UNDERLINE "Winning conditions:" ANSI_RESET_UNDERLINE << std::endl;
    std::cout << " A player immediately wins if they achieve one of the following:" << std::endl;
    std::cout << " 1. An alignment of three identical circles (same size)." << std::endl;
    std::cout << " 2. An alignment of three circles in increasing or decreasing size." << std::endl;
    std::cout << " 3. A complete stack of Small, Medium, and Large circles" << std::endl;
    std::cout << "    on the same cell." << std::endl;

    std::cout << std::endl;
    std::cout << ANSI_UNDERLINE "Game modes:" ANSI_RESET_UNDERLINE << std::endl;
    std::cout << " - 4 Players: each player controls one color." << std::endl;
    std::cout << " - 2 Players: each player controls two colors alternately." << std::endl;
    std::cout << "   Victory is valid for a single color only." << std::endl;

    std::cout << std::endl;
    std::cout << ANSI_UNDERLINE "Game commands:" ANSI_RESET_UNDERLINE << std::endl;
    std::cout << " Use the arrow keys to move the cursor." << std::endl;
    std::cout << " Press " << key("[ENTER]") " to select a circle size or a board position." << std::endl;
    std::cout << " The enter coordinates to place the selected circle (eg.: A1)." << std::endl;
    std::cout << " A turn consists of selecting a size, then placing it on the board." << std::endl;

    std::cout << ANSI_BLUE;
    std::cout << "                              [UP]" << std::endl;
    std::cout << "                             [ENTER]" << std::endl;
    std::cout << "                             [DOWN]" << std::endl;
    std::cout << ANSI_RESET;

    std::cout << std::endl;
    CONTINUE_ON_ENTER_PROMPT

    return true;
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