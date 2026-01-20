#pragma once

#include <array>

#include "Frame.hpp"

class Board
{
private:
    std::array<std::array<Frame, 3>, 3> frames; // X,Y

public:
    Board();
    ~Board();
    std::string toString() const;
};