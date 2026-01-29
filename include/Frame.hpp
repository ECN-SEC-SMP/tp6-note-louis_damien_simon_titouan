#pragma once

#include <string>

#include "Circle.hpp"

/**
 * @class Frame
 * @brief Represents a frame containing three circles of different sizes
 *
 * The Frame class manages a collection of circles (small, medium, and large)
 * and provides functionality to place circles of specific colors and sizes
 * onto the frame.
 */
class Frame
{
private:
    Circle *smallCircle;
    Circle *mediumCircle;
    Circle *largeCircle;

public:
    /**
     * @brief Default constructor
     *
     * Initializes a new Frame with empty circles.
     * An empty circle is a nullptr.
     */
    Frame();

    /**
     * @brief Copy constructor
     *
     * Creates a deep copy of the given Frame object
     *
     * @param frame The Frame object to copy
     */
    Frame(const Frame &frame);

    /**
     * @brief Destructor
     *
     * Releases all dynamically allocated memory for circles
     */
    ~Frame();

    /**
     * @brief Retrieves a circle from the frame by its size
     *
     * @param size The CircleSize specifying which circle to retrieve
     * @return Circle* Pointer to the requested circle, or nullptr if not found
     */
    Circle *getCircle(CircleSize size) const;

    void removeCircle(CircleColor c, CircleSize s);

    /**
     * @brief Attempts to place a circle on the frame
     *
     * Tries to place a circle of the specified color and size on the frame.
     * The placement may fail if the target circle is already occupied.
     *
     * @param color The CircleColor of the circle to place
     * @param size The CircleSize of the circle to place
     * @return bool true if the circle was successfully placed, false otherwise
     */
    bool tryToPlace(CircleColor color, CircleSize size);

    /**
     * @brief Converts the frame to a string representation
     *
     * @return std::string A string representation of the current frame state
     */
    std::string toString() const;

    /**
     * @brief Assignment operator
     *
     * Assigns a deep copy of the given Frame to this Frame object
     *
     * @param frame The Frame object to assign
     * @return Frame& Reference to this Frame object after assignment
     */
    Frame &operator=(const Frame &frame);
};