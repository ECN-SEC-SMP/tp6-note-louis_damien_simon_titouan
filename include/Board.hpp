#pragma once

#include <array>

#include "BoardStyle.hpp"
#include "Frame.hpp"

#define BOARD_SIZE 3

struct BoardStyle_t
{
    std::string horizontalSeparator = HORIZONTAL_SEPARATOR_SIMPLE;
    std::string verticalSeparator = VERTICAL_SEPARATOR_SIMPLE;

    std::string node_middle = NODE_MIDDLE_SIMPLE;
    std::string node_horizontal = NODE_HORIZONTAL_SIMPLE;
    std::string node_vertical = NODE_VERTICAL_SIMPLE;

    std::string node_top = NODE_TOP_SIMPLE;
    std::string node_left = NODE_LEFT_SIMPLE;
    std::string node_right = NODE_RIGHT_SIMPLE;
    std::string node_bottom = NODE_BOTTOM_SIMPLE;

    std::string node_top_left = NODE_TOP_LEFT_SIMPLE;
    std::string node_top_right = NODE_TOP_RIGHT_SIMPLE;
    std::string node_bottom_left = NODE_BOTTOM_LEFT_SIMPLE;
    std::string node_bottom_right = NODE_BOTTOM_RIGHT_SIMPLE;
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
     * It contains the characters used for horizontal and vertical separators, and grid nodes.
     */
    BoardStyle_t boardStyle;

    /**
     * @brief Converts a coordinate value to its corresponding board array index.
     *
     * This helper function maps a given coordinate to the internal 0-based index used in the `frames` array.
     * It ensures that external coordinates correctly access the intended row or column.
     *
     * @param coord The coordinate value to convert.
     * @return int The corresponding 0-based index in the board's `frames` array.
     *
     * @note The function assumes that the input `coord` is within the valid range for the board.
     */
    int axisIndexFromCoord(int coord) const;

    /**
     * @brief Computes the grid node representation at the specified coordinates.
     *
     * @param x The x-coordinate of the position on the board.
     * @param y The y-coordinate of the position on the board.
     *
     * @return std::string The string representation of the grid node at position (x, y).
     */
    std::string computeGridNode(int x, int y) const;

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