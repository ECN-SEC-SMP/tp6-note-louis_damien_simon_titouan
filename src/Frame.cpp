#include <array>

#include "ANSI.hpp"
#include "Frame.hpp"

/* Utils -------------------------------------------------------------------- */

static std::string getAnsiCodeFromCircleColor(CircleColor color);
static std::string concatFrameStringArray(std::array<std::string, 5> stringArray);

/* Constructors ------------------------------------------------------------- */

Frame::Frame()
{
    this->smallCircle = nullptr;
    this->mediumCircle = nullptr;
    this->largeCircle = nullptr;
}

Frame::Frame(const Frame &frameToCopy) : smallCircle(nullptr),
                                         mediumCircle(nullptr),
                                         largeCircle(nullptr)
{
    if (frameToCopy.smallCircle != nullptr)
        this->smallCircle = new Circle(*frameToCopy.smallCircle);
    if (frameToCopy.mediumCircle != nullptr)
        this->mediumCircle = new Circle(*frameToCopy.mediumCircle);
    if (frameToCopy.largeCircle != nullptr)
        this->largeCircle = new Circle(*frameToCopy.largeCircle);
}

Frame::~Frame()
{
    delete this->smallCircle;
    delete this->mediumCircle;
    delete this->largeCircle;
};

/* Methods ------------------------------------------------------------------ */

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

bool Frame::tryToPlace(CircleColor color, CircleSize size)
{
    switch (size)
    {
    case SMALL:
        if (this->smallCircle == nullptr)
        {
            this->smallCircle = new Circle(color, size);
            return true;
        }
        break;

    case MEDIUM:
        if (this->mediumCircle == nullptr)
        {
            this->mediumCircle = new Circle(color, size);
            return true;
        }
        break;

    case LARGE:
        if (this->largeCircle == nullptr)
        {
            this->largeCircle = new Circle(color, size);
            return true;
        }
        break;
    }

    return false;
}
std::string Frame::toString() const
{
    // Initialize array with spaces for each layer (large, medium, small, medium, large)
    std::array<std::string, 5> frameStrArray = {" ", " ", " ", " ", " "};

    // Add large circle brackets if present
    if (this->largeCircle != nullptr)
    {
        std::string circleAnsiColor = getAnsiCodeFromCircleColor(this->largeCircle->getColor());
        frameStrArray[0] = circleAnsiColor + "(";
        frameStrArray[4] = circleAnsiColor + ")";
    }

    // Add medium circle brackets if present
    if (this->mediumCircle != nullptr)
    {
        std::string circleAnsiColor = getAnsiCodeFromCircleColor(this->mediumCircle->getColor());
        frameStrArray[1] = circleAnsiColor + "(";
        frameStrArray[3] = circleAnsiColor + ")";
    }

    // Add small circle symbol if present
    if (this->smallCircle != nullptr)
    {
        std::string circleAnsiColor = getAnsiCodeFromCircleColor(this->smallCircle->getColor());
        frameStrArray[2] = circleAnsiColor + "o";
    }

    // Concatenate all elements and apply bold formatting
    return ANSI_BOLD + concatFrameStringArray(frameStrArray) + ANSI_RESET;
}

/* Operators ---------------------------------------------------------------- */

Frame &Frame::operator=(const Frame &frame)
{
    if (this == &frame)
        return *this;

    delete this->smallCircle;
    delete this->mediumCircle;
    delete this->largeCircle;

    this->smallCircle = nullptr;
    this->mediumCircle = nullptr;
    this->largeCircle = nullptr;

    if (frame.smallCircle != nullptr)
        this->smallCircle = new Circle(*frame.smallCircle);
    if (frame.mediumCircle != nullptr)
        this->mediumCircle = new Circle(*frame.mediumCircle);
    if (frame.largeCircle != nullptr)
        this->largeCircle = new Circle(*frame.largeCircle);

    return *this;
}

/* Utils -------------------------------------------------------------------- */

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

static std::string concatFrameStringArray(std::array<std::string, 5> stringArray)
{
    std::string frameStr;
    for (size_t idx = 0; idx < stringArray.size(); idx++)
    {
        frameStr += stringArray[idx];
    }

    return frameStr;
}