#pragma once

enum CircleColor
{
    RED,
    GREEN,
    BLUE,
    MAGENTA
};

enum CircleSize
{
    SMALL,
    MEDIUM,
    LARGE
};

class Circle
{
private:
    CircleColor color;
    CircleSize size;

public:
    Circle(CircleColor color, CircleSize size);
    ~Circle();
    CircleColor getColor() const;
    CircleSize getSize() const;
};