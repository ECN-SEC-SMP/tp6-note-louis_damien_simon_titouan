#include <gtest/gtest.h>
#include "ANSI.hpp"
#include "Frame.hpp"

#define FORMATTING ANSI_BOLD
#define CIRCLE_COLOR_1 ORANGE
#define CIRCLE_COLOR_2 RED
#define CIRCLE_COLOR_3 BLUE
#define CIRCLE_ANSI_COLOR_1 ANSI_ORANGE
#define CIRCLE_ANSI_COLOR_2 ANSI_RED
#define CIRCLE_ANSI_COLOR_3 ANSI_BLUE

/* Test deep copy with constructor and assignement operator */

TEST(Frame_CopyConstructor, createsDeepCopy)
{
    /* Setup */
    CircleColor circleColor = CIRCLE_COLOR_1;
    CircleSize circleSize = SMALL;
    Frame f1;
    f1.tryToPlace(circleColor, circleSize);
    Frame f2(f1);

    /* Test */
    // Check that circle has been copied
    EXPECT_NE(f2.getCircle(circleSize), nullptr);

    // Check that pointer is different (deep copy)
    EXPECT_NE(f2.getCircle(circleSize), f1.getCircle(circleSize));

    // Check that data is the same
    EXPECT_EQ(f2.getCircle(circleSize)->getColor(), f1.getCircle(circleSize)->getColor());
}

TEST(Frame_AssignementOperator, createsDeepCopy)
{
    /* Setup */
    CircleColor circleColor = CIRCLE_COLOR_2;
    CircleSize circleSize = MEDIUM;
    Frame f1;
    f1.tryToPlace(circleColor, circleSize);
    Frame f2;
    f2 = f1;

    /* Test */
    // Check that circle has been copied
    EXPECT_NE(f2.getCircle(circleSize), nullptr);

    // Check that pointer is different (deep copy)
    EXPECT_NE(f2.getCircle(circleSize), f1.getCircle(circleSize));

    // Check that data is the same
    EXPECT_EQ(f2.getCircle(circleSize)->getColor(), f1.getCircle(circleSize)->getColor());
}

/* toString() --------------------------------------------------------------- */
/* Test combinations of circles (color used: black) */

TEST(Frame_toString, EmptyFrame)
{
    /* Setup */
    Frame frame = Frame();

    /* Test */
    std::string expected_str = FORMATTING "     " ANSI_RESET;
    EXPECT_EQ(frame.toString(), expected_str);
}

TEST(Frame_toString, OnlySmallCircle)
{
    /* Setup */
    Frame frame = Frame();
    frame.tryToPlace(CIRCLE_COLOR_1, SMALL);

    /* Test */
    std::string expected_str = FORMATTING "  " CIRCLE_ANSI_COLOR_1 "o  " ANSI_RESET;
    EXPECT_EQ(frame.toString(), expected_str);
}

TEST(Frame_toString, OnlyMediumCircle)
{
    /* Setup */
    Frame frame = Frame();
    frame.tryToPlace(CIRCLE_COLOR_1, MEDIUM);

    /* Test */
    std::string expected_str = FORMATTING " " CIRCLE_ANSI_COLOR_1 "( ";
    expected_str += CIRCLE_ANSI_COLOR_1 ") " ANSI_RESET;
    EXPECT_EQ(frame.toString(), expected_str);
}

TEST(Frame_toString, OnlyLargeCircle)
{
    /* Setup */
    Frame frame = Frame();
    frame.tryToPlace(CIRCLE_COLOR_1, LARGE);

    /* Test */
    std::string expected_str = FORMATTING CIRCLE_ANSI_COLOR_1 "(   ";
    expected_str += CIRCLE_ANSI_COLOR_1 ")" ANSI_RESET;
    EXPECT_EQ(frame.toString(), expected_str);
}

TEST(Frame_toString, SmallAndMediumCircles)
{
    /* Setup */
    Frame frame = Frame();
    frame.tryToPlace(CIRCLE_COLOR_1, SMALL);
    frame.tryToPlace(CIRCLE_COLOR_2, MEDIUM);

    /* Test */
    std::string expected_str = FORMATTING " ";
    expected_str += CIRCLE_ANSI_COLOR_2 "(";
    expected_str += CIRCLE_ANSI_COLOR_1 "o";
    expected_str += CIRCLE_ANSI_COLOR_2 ") " ANSI_RESET;
    EXPECT_EQ(frame.toString(), expected_str);
}

TEST(Frame_toString, SmallAndLargeCircles)
{
    /* Setup */
    Frame frame = Frame();
    frame.tryToPlace(CIRCLE_COLOR_1, SMALL);
    frame.tryToPlace(CIRCLE_COLOR_2, LARGE);

    /* Test */
    std::string expected_str = FORMATTING CIRCLE_ANSI_COLOR_2 "( ";
    expected_str += CIRCLE_ANSI_COLOR_1 "o ";
    expected_str += CIRCLE_ANSI_COLOR_2 ")" ANSI_RESET;
    EXPECT_EQ(frame.toString(), expected_str);
}

TEST(Frame_toString, MediumAndLargeCircles)
{
    /* Setup */
    Frame frame = Frame();
    frame.tryToPlace(CIRCLE_COLOR_1, MEDIUM);
    frame.tryToPlace(CIRCLE_COLOR_2, LARGE);

    /* Test */
    std::string expected_str = FORMATTING CIRCLE_ANSI_COLOR_2 "(";
    expected_str += CIRCLE_ANSI_COLOR_1 "( " CIRCLE_ANSI_COLOR_1 ")" CIRCLE_ANSI_COLOR_2 ")" ANSI_RESET;
    EXPECT_EQ(frame.toString(), expected_str);
}

TEST(Frame_toString, FullFrame)
{
    /* Setup */
    Frame frame = Frame();
    frame.tryToPlace(CIRCLE_COLOR_1, SMALL);
    frame.tryToPlace(CIRCLE_COLOR_2, MEDIUM);
    frame.tryToPlace(CIRCLE_COLOR_3, LARGE);

    /* Test */
    std::string expected_str = FORMATTING CIRCLE_ANSI_COLOR_3 "(";
    expected_str += CIRCLE_ANSI_COLOR_2 "(";
    expected_str += CIRCLE_ANSI_COLOR_1 "o";
    expected_str += CIRCLE_ANSI_COLOR_2 ")";
    expected_str += CIRCLE_ANSI_COLOR_3 ")" ANSI_RESET;
    EXPECT_EQ(frame.toString(), expected_str);
}

/* Test different circle colors */

TEST(Frame_toString, SmallRedCircle)
{
    Frame frame = Frame();
    frame.tryToPlace(RED, SMALL);
    std::string expected_str = FORMATTING "  " ANSI_RED "o  " ANSI_RESET;
    EXPECT_EQ(frame.toString(), expected_str);
}

TEST(Frame_toString, SmallGreenCircle)
{
    Frame frame = Frame();
    frame.tryToPlace(GREEN, SMALL);
    std::string expected_str = FORMATTING "  " ANSI_GREEN "o  " ANSI_RESET;
    EXPECT_EQ(frame.toString(), expected_str);
}

TEST(Frame_toString, SmallBlueCircle)
{
    Frame frame = Frame();
    frame.tryToPlace(BLUE, SMALL);
    std::string expected_str = FORMATTING "  " ANSI_BLUE "o  " ANSI_RESET;
    EXPECT_EQ(frame.toString(), expected_str);
}

TEST(Frame_toString, SmallOrangeCircle)
{
    Frame frame = Frame();
    frame.tryToPlace(ORANGE, SMALL);
    std::string expected_str = FORMATTING "  " ANSI_ORANGE "o  " ANSI_RESET;
    EXPECT_EQ(frame.toString(), expected_str);
}

TEST(Frame_tryToPlace, refusesTwoSmallCircles)
{
    Frame frame = Frame();
    EXPECT_EQ(frame.tryToPlace(CIRCLE_COLOR_1, SMALL), true);
    EXPECT_EQ(frame.tryToPlace(CIRCLE_COLOR_2, SMALL), false);
    EXPECT_EQ(frame.getCircle(SMALL)->getColor(), CIRCLE_COLOR_1);
}
TEST(Frame_tryToPlace, refusesTwoMediumCircles)
{
    Frame frame = Frame();
    EXPECT_EQ(frame.tryToPlace(CIRCLE_COLOR_1, MEDIUM), true);
    EXPECT_EQ(frame.tryToPlace(CIRCLE_COLOR_2, MEDIUM), false);
    EXPECT_EQ(frame.getCircle(MEDIUM)->getColor(), CIRCLE_COLOR_1);
}
TEST(Frame_tryToPlace, refusesTwoLargeCircles)
{
    Frame frame = Frame();
    EXPECT_EQ(frame.tryToPlace(CIRCLE_COLOR_1, LARGE), true);
    EXPECT_EQ(frame.tryToPlace(CIRCLE_COLOR_2, LARGE), false);
    EXPECT_EQ(frame.getCircle(LARGE)->getColor(), CIRCLE_COLOR_1);
}