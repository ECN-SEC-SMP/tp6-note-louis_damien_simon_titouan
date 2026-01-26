#pragma once

#include <array>

#include "Frame.hpp"

struct BoardStyle_t
{
    std::string horizontal_wall = "-----";
    std::string vertical_wall = "|";
    std::string wall_node = "+";
};

class Board
{
private:
    std::array<std::array<Frame, 3>, 3> frames; // X,Y
    BoardStyle_t boardStyle;

public:
    Board();
    ~Board();
    std::array<std::array<Frame, 3>, 3> &getFrames();
    std::string toString() const;
};