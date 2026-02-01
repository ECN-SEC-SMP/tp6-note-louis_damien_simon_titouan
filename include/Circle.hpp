#pragma once

enum CircleColor
{
    RED,
    GREEN,
    BLUE,
    ORANGE
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
    /* Constructors */
    /**
     * @brief Construct a new Circle object
     *
     * @param color
     * @param size
     */
    Circle(CircleColor color, CircleSize size);

    /**
     * @brief Destroy the Circle object
     *
     */
    ~Circle();

    /* Getters */
    /**
     * @brief Get the circle color
     *
     * @return CircleColor
     */
    CircleColor getColor() const;
    /**
     * @brief Get the circle size
     *
     * @return CircleSize
     */
    CircleSize getSize() const;
};