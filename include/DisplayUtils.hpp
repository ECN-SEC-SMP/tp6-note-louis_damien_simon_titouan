#pragma once

#include <vector>
#include <iostream>

#include "ANSI.hpp"
#include "Player.hpp"
#include "Otrio.hpp"
#include "Board.hpp"

/// @brief Game banner to display above each windows
#define GAME_ASCII_BANNER ANSI_BOLD ANSI_BLUE "\
  ___  _        _       \n\
 / _ \\| |_ _ __(_) ___  \n\
| | | | __| '__| |/ _ \\ \n\
| |_| | |_| |  | | (_) |\n\
 \\___/ \\__|_|  |_|\\___/ \n\
    " ANSI_RESET_BOLD ANSI_ITALIC ANSI_UNDERLINE "By Les Quadruples Montres\n\n" ANSI_RESET

////////////////////////////////////////////////////////////////////////////////
//                                  Macros                                    //
////////////////////////////////////////////////////////////////////////////////
#define CONTINUE_ON_ENTER_PROMPT                            \
  std::cin.clear();                                         \
  std::cout << "Press [ENTER] to continue..." << std::endl; \
  std::cin.ignore(100, '\n');
#define key(str) ANSI_BLUE str ANSI_RESET
#define red_word(str) ANSI_RED str ANSI_RESET

/**
 * @namespace Render
 * @brief Namespace containing utility functions for displaying game elements.
 */
namespace Render
{
  /**
   * @brief Get the render of the Player List for display
   *
   * @param[in] players List of players
   * @return std::string
   */
  std::string playerList(std::vector<Player *> players);

  /**
   * @brief Get the render of the Game Mode for display
   *
   * @param[in] mode Game Mode
   * @return std::string
   */
  std::string gameMode(OtrioGameMode mode);

  /**
   * @brief Converts a Board object to its string representation.
   *
   * @param board The Board object to be converted into a displayable format.
   * @return std::string A string representation of the board suitable for console output.
   */
  std::string board(const Board &board);

  /**
   * @brief Generates a formatted string representation of a player's inventory.
   *
   * This function creates a visual display of all items currently held by the specified player.
   * The inventory is formatted as a string suitable for console output or display purposes.
   *
   * @param player A pointer to the Player object whose inventory is to be displayed.
   *               The pointer must not be null.
   *
   * @return A std::string containing the formatted inventory display. This include the
   *         player name, and string representation of the circles.
   *
   * @see Player
   */
  std::string playerInventory(Player *player);

  /**
   * @brief Generates a string representation of all players' inventories.
   *
   * @param players A vector of pointers to Player objects whose inventories should be displayed.
   * @return std::string A formatted string containing all players' inventory information.
   */
  std::string playersInventory(std::vector<Player *> players);
} // namespace Render
