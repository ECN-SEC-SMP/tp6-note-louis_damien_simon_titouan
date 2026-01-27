#pragma once

#include <array>

#include "Frame.hpp"

struct BoardStyle_t
{
    std::string horizontalWall = "-----";
    std::string verticalWall = "¦";
    std::string wallNode = "+";
};

/**
 * @class Board
 * @brief Manages the game board structure and visual representation for the Otrio game.
 *
 * The Board class handles a 3x3 grid of Frames that constitute the main playing area.
 * It manages the board's appearance through a configurable BoardStyle and provides
 * methods to access and display the board state.
 * Each frame can contain game pieces and has its own visual representation. The board
 * style determines how the frames and their boundaries are rendered to the player.
 */
class Board
{
private:
    /** @brief 2D array representing the game board frames
     *  @details A 3x3 matrix of Frame objects where the first dimension represents
     *           the X coordinate and the second dimension represents the Y coordinate.
     */
    std::array<std::array<Frame, 3>, 3> frames;

    /**
     * @brief Enumeration or type defining the visual style of the game board.
     *
     * This member variable stores the current style configuration for the board's appearance
     * and rendering. It determines how the board is displayed to the player.
     * It contains the characters used for horizontal and vertical walls, and wall nodes.
     */
    BoardStyle_t boardStyle;

public:
    /**
     * @brief Default constructor for the Board class.
     *
     * Initializes a new Board instance with default settings. Sets up the 3x3 grid
     * of frames and applies the default board style.
     */
    Board();

    /**
     * @brief Destructor for the Board class.
     *
     * Cleans up resources allocated by the Board instance.
     */
    ~Board();

    /**
     * @brief Retrieves the frames array from the board.
     *
     * @return A reference to the 3x3 array of Frame objects that make up the board.
     *         This allows direct access to and modification of individual frames.
     */
    std::array<std::array<Frame, 3>, 3> &getFrames();

    /**
     * @brief Generates a string representation of the board.
     *
     * Creates a formatted string that displays the current state of the board,
     * including all frames and their contents, according to the current board style.
     *
     * @return A std::string containing the visual representation of the board.
     * @note The string representation respects the configured BoardStyle.
     */
    std::string toString() const;
};