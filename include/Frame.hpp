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
    /* Constructors */
    Frame();
    Frame(const Frame &frame);
    ~Frame();

    /* Methods */
    Circle *getCircle(CircleSize size);
    bool tryToPlace(CircleColor color, CircleSize size);
    std::string toString() const;

    /* Operators */
    Frame &operator=(const Frame &frame);
};