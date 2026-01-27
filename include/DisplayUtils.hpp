#pragma once

#include <vector>
#include <iostream>

#include "ANSI.hpp"
#include "Player.hpp"
#include "Otrio.hpp"

/// @brief Game banner to display above each windows
#define GAME_ASCII_BANNER ANSI_BOLD ANSI_BLUE "\
  ___  _        _       \n\
 / _ \\| |_ _ __(_) ___  \n\
| | | | __| '__| |/ _ \\ \n\
| |_| | |_| |  | | (_) |\n\
 \\___/ \\__|_|  |_|\\___/ \n\
    " ANSI_RESET_BOLD ANSI_ITALIC ANSI_UNDERLINE "By Les Quadruples Montres\n\n" ANSI_RESET

/* Board ==================================================================== */
/* Grid */
#define NODE "┼"
#define HORIZONTAL_GRID "────"
#define VERTICAL_GRID "│"

/* DOUBLE_WALLS ------------------------------------------------------------- */
/* Walls */
#define HORIZONTAL_WALL_DOUBLE "════"
#define VERTICAL_WALL_DOUBLE "║"

/* Wall nodes */
#define NODE_MIDDLE_DOUBLE "╬"
#define NODE_HORIZONTAL_DOUBLE "═"
#define NODE_VERTICAL_DOUBLE "║"

#define NODE_TOP_DOUBLE "╦"
#define NODE_LEFT_DOUBLE "╠"
#define NODE_RIGHT_DOUBLE "╣"
#define NODE_BOTTOM_DOUBLE "╩"

#define NODE_TOP_LEFT_DOUBLE "╔"
#define NODE_TOP_RIGHT_DOUBLE "╗"
#define NODE_BOTTOM_LEFT_DOUBLE "╚"
#define NODE_BOTTOM_RIGHT_DOUBLE "╝"

/* SIMPLE_WALLS ------------------------------------------------------------- */
/* Walls */
#define HORIZONTAL_WALL_SIMPLE "────"
#define VERTICAL_WALL_SIMPLE "│"

/* Wall nodes */
#define NODE_MIDDLE_SIMPLE "┼"
#define NODE_HORIZONTAL_SIMPLE "─"
#define NODE_VERTICAL_SIMPLE "│"

#define NODE_TOP_SIMPLE "┬"
#define NODE_LEFT_SIMPLE "├"
#define NODE_RIGHT_SIMPLE "┤"
#define NODE_BOTTOM_SIMPLE "┴"

#define NODE_TOP_LEFT_SIMPLE "┌"
#define NODE_TOP_RIGHT_SIMPLE "┐"
#define NODE_BOTTOM_LEFT_SIMPLE "└"
#define NODE_BOTTOM_RIGHT_SIMPLE "┘"

#define EMPTY_FRAME "    "

/* Scoreboard =============================================================== */
#define TOP_LEFT_CORNER "┌"
#define TOP_RIGHT_CORNER "┐"
#define BOTTOM_LEFT_CORNER "└"
#define BOTTOM_RIGHT_CORNER "┘"
#define HORIZONTAL_BORDER "─"
#define VERTICAL_BORDER "│"

////////////////////////////////////////////////////////////////////////////////
//                                  Macros                                    //
////////////////////////////////////////////////////////////////////////////////
#define CONTINUE_ON_ENTER_PROMPT                            \
  std::cin.clear();                                         \
  std::cout << "Press [ENTER] to continue..." << std::endl; \
  std::cin.ignore(100, '\n');
#define key(str) ANSI_BLUE str ANSI_RESET
#define red_word(str) ANSI_RED str ANSI_RESET

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
} // namespace Render
