#include <stdexcept>
#include "Board.hpp"

/* Constructors ------------------------------------------------------------- */

Board::Board() = default;

Board::~Board() = default;

/* Getters ------------------------------------------------------------------ */

std::array<std::array<Frame, 3>, 3> &Board::getFrames()
{
    return this->frames;
}

/* Methods ------------------------------------------------------------------ */

std::string Board::toString() const
{
    std::string outputString;

    /* Iterate line by line */
    for (int y = 0; y < BOARD_SIZE; y++)
    {
        /* For each line, create two strings:
            - walls: it contains the top walls of the line (horizontal walls)
            - contents: it contains the vertical walls and the frames content
        */
        std::string walls = "";
        std::string contents = "";

        for (int x = 0; x < BOARD_SIZE; x++)
        {
            /* For each frame, add strings for:
                - top wall and top left corner (walls):
                    ╔═════+
                    ¦     ¦
                    +-----+
                - left wall and content of the frame (contents):
                    +-----+
                    ║XXXXX¦
                    +-----+
            */
            walls += this->computeWallNode(x, y);
            walls += this->boardStyle.horizontalWall;

            contents += this->boardStyle.verticalWall;
            contents += this->frames[x][y].toString();

            /* Right border */
            if (x == BOARD_SIZE - 1)
            {
                walls += this->computeWallNode(x + 1, y);
                contents += this->boardStyle.verticalWall;
            }
        }

        /* Add frame top wall and frame content to output string */
        outputString += walls + "\n";
        outputString += contents + "\n";
    }

    /* Bottom border */
    std::string walls;
    for (int x = 0; x < BOARD_SIZE; x++)
    {
        walls += this->computeWallNode(x, BOARD_SIZE);
        walls += this->boardStyle.horizontalWall;
    }

    /* Bottom right corner */
    walls += this->computeWallNode(BOARD_SIZE, BOARD_SIZE);

    /* Add bottom border */
    outputString += walls + "\n";

    return outputString;
}

int Board::axisIndexFromCoord(int coord) const
{
    /** Axis index returned:
     * 0 = start
     * 1 = middle
     * 2 = end
     */
    if (coord == 0)
        return 0;
    else if (coord > 0 and coord < BOARD_SIZE)
        return 1;
    else if (coord == BOARD_SIZE)
        return 2;
    else
        throw std::invalid_argument("coord must be in the range {0," + std::to_string(BOARD_SIZE) + "}");
}

std::string Board::computeWallNode(int x, int y) const
{
    int xIndex = this->axisIndexFromCoord(x);
    int yIndex = this->axisIndexFromCoord(y);

    const std::string *nodesTable[3][3] = {
        {&boardStyle.node_top_left, &boardStyle.node_top, &boardStyle.node_top_right},
        {&boardStyle.node_left, &boardStyle.node_middle, &boardStyle.node_right},
        {&boardStyle.node_bottom_left, &boardStyle.node_bottom, &boardStyle.node_bottom_right}};

    return *nodesTable[yIndex][xIndex];
}