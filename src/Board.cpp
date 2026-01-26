#include "Board.hpp"

#define BOARD_SIZE 3

Board::Board() = default;

Board::~Board() = default;

std::array<std::array<Frame, 3>, 3> &Board::getFrames()
{
    return this->frames;
}

std::string Board::toString() const
{
    std::string output_string;

    for (int y = 0; y < BOARD_SIZE; y++)
    {
        std::string walls = "";
        std::string contents = "";

        for (int x = 0; x < BOARD_SIZE; x++)
        {
            walls += this->boardStyle.wall_node;
            walls += this->boardStyle.horizontal_wall;

            contents += this->boardStyle.vertical_wall;
            contents += this->frames[x][y].toString();

            /* Right border */
            if (x == BOARD_SIZE - 1)
            {
                walls += this->boardStyle.wall_node;
                contents += this->boardStyle.vertical_wall;
            }
        }

        output_string += walls + "\n";
        output_string += contents + "\n";
    }

    /* Bottom border */
    std::string walls;
    for (int x = 0; x < BOARD_SIZE; x++)
    {
        walls += this->boardStyle.wall_node;
        walls += this->boardStyle.horizontal_wall;
    }
    output_string += walls;
    output_string += this->boardStyle.wall_node;

    return output_string;
}