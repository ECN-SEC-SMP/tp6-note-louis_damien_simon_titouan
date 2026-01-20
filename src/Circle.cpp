#include "Circle.hpp"

Circle::Circle(CircleColor color, CircleSize size)
{
    this->color = color;
    this->size = size;
}

Circle::~Circle() = default;

CircleColor Circle::getColor() const
{
    return this->color;
}

CircleSize Circle::getSize() const
{
    return this->size;
}