#pragma once

#include <array>

#include "Frame.hpp"

struct BoardStyle_t
{
    std::string horizontalWall = "-----";
    std::string verticalWall = "|";
    std::string wallNode = "+";
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