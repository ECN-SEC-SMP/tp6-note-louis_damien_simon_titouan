#include "Board.hpp"

#define BOARD_SIZE 3

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
    std::string output_string;

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
            walls += this->boardStyle.wallNode;
            walls += this->boardStyle.horizontalWall;

            contents += this->boardStyle.verticalWall;
            contents += this->frames[x][y].toString();

            /* Right border */
            if (x == BOARD_SIZE - 1)
            {
                walls += this->boardStyle.wallNode;
                contents += this->boardStyle.verticalWall;
            }
        }

        /* Add frame top wall and frame content to output string */
        output_string += walls + "\n";
        output_string += contents + "\n";
    }

    /* Bottom border */
    std::string walls;
    for (int x = 0; x < BOARD_SIZE; x++)
    {
        walls += this->boardStyle.wallNode;
        walls += this->boardStyle.horizontalWall;
    }
    output_string += walls;
    output_string += this->boardStyle.wallNode;

    return output_string;
}