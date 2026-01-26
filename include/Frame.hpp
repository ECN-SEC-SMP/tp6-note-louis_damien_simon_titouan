#pragma once

#include <string>

#include "Circle.hpp"

class Frame
{
private:
    Circle *smallCircle;
    Circle *mediumCircle;
    Circle *largeCircle;

public:
    Frame();
    ~Frame();
    Circle *getCircle(CircleSize size);
    bool tryToPlace(CircleColor color, CircleSize size);
    std::string toString() const;
};