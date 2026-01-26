#include <array>

#include "ANSI.hpp"
#include "Frame.hpp"

static std::string getAnsiCodeFromCircleColor(CircleColor color);
static std::string concatFrameStringArray(std::array<std::string, 5> string_array);

Frame::Frame()
{
    this->smallCircle = nullptr;
    this->mediumCircle = nullptr;
    this->largeCircle = nullptr;
}

Frame::~Frame() = default;

Circle *Frame::getCircle(CircleSize size)
{
    switch (size)
    {
    case SMALL:
        return this->smallCircle;
    case MEDIUM:
        return this->mediumCircle;
    case LARGE:
        return this->largeCircle;
    default:
        return nullptr;
    }
}

bool Frame::tryToPlace(Circle *circle)
{
    switch (circle->getSize())
    {
    case SMALL:
        if (this->smallCircle == nullptr)
        {
            this->smallCircle = circle;
            return true;
        }

    case MEDIUM:
        if (this->mediumCircle == nullptr)
        {
            this->mediumCircle = circle;
            return true;
        }

    case LARGE:
        if (this->largeCircle == nullptr)
        {
            this->largeCircle = circle;
            return true;
        }
    }

    return false;
}

std::string Frame::toString() const
{
    std::array<std::string, 5> frame_str_array = {" ", " ", " ", " ", " "};

    if (this->largeCircle != nullptr)
    {
        std::string circle_ansi_color = getAnsiCodeFromCircleColor(this->largeCircle->getColor());
        frame_str_array[0] = circle_ansi_color + "(";
        frame_str_array[4] = circle_ansi_color + ")";
    }

    if (this->mediumCircle != nullptr)
    {
        std::string circle_ansi_color = getAnsiCodeFromCircleColor(this->mediumCircle->getColor());
        frame_str_array[1] = circle_ansi_color + "(";
        frame_str_array[3] = circle_ansi_color + ")";
    }

    if (this->smallCircle != nullptr)
    {
        std::string circle_ansi_color = getAnsiCodeFromCircleColor(this->smallCircle->getColor());
        frame_str_array[2] = circle_ansi_color + "o";
    }

    return ANSI_BOLD + concatFrameStringArray(frame_str_array) + ANSI_RESET;
}

static std::string getAnsiCodeFromCircleColor(CircleColor color)
{
    switch (color)
    {
    case RED:
        return ANSI_RED;
    case GREEN:
        return ANSI_GREEN;
    case BLUE:
        return ANSI_BLUE;
    case ORANGE:
        return ANSI_ORANGE;

    default:
        return "";
    }
}

static std::string concatFrameStringArray(std::array<std::string, 5> string_array)
{
    std::string frame_str;
    for (size_t idx = 0; idx < string_array.size(); idx++)
    {
        frame_str += string_array[idx];
    }

    return frame_str;
}