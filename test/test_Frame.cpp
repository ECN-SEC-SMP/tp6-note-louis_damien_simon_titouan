#include <gtest/gtest.h>
#include "ANSI.hpp"
#include "Frame.hpp"

/* Test combinations of circles (color used: black) */

#define FORMATTING ANSI_BOLD
#define CIRCLE_COLOR_1 ORANGE
#define CIRCLE_COLOR_2 ORANGE
#define CIRCLE_COLOR_3 ORANGE
#define CIRCLE_ANSI_COLOR_1 ANSI_ORANGE
#define CIRCLE_ANSI_COLOR_2 ANSI_ORANGE
#define CIRCLE_ANSI_COLOR_3 ANSI_ORANGE

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
    frame.tryToPlace(Circle(CIRCLE_COLOR_1, SMALL));

    /* Test */
    std::string expected_str = FORMATTING "  " CIRCLE_ANSI_COLOR_1 "o  " ANSI_RESET;
    EXPECT_EQ(frame.toString(), expected_str);
}

TEST(Frame_toString, OnlyMediumCircle)
{
    /* Setup */
    Frame frame = Frame();
    frame.tryToPlace(Circle(CIRCLE_COLOR_1, MEDIUM));

    /* Test */
    std::string expected_str = FORMATTING " " CIRCLE_ANSI_COLOR_1 "( ";
    expected_str += CIRCLE_ANSI_COLOR_1 ") " ANSI_RESET;
    EXPECT_EQ(frame.toString(), expected_str);
}

TEST(Frame_toString, OnlyLargeCircle)
{
    /* Setup */
    Frame frame = Frame();
    frame.tryToPlace(Circle(CIRCLE_COLOR_1, LARGE));

    /* Test */
    std::string expected_str = FORMATTING CIRCLE_ANSI_COLOR_1 "(   ";
    expected_str += CIRCLE_ANSI_COLOR_1 ")" ANSI_RESET;
    EXPECT_EQ(frame.toString(), expected_str);
}

TEST(Frame_toString, SmallAndMediumCircles)
{
    /* Setup */
    Frame frame = Frame();
    frame.tryToPlace(Circle(CIRCLE_COLOR_1, SMALL));
    frame.tryToPlace(Circle(CIRCLE_COLOR_2, MEDIUM));

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
    frame.tryToPlace(Circle(CIRCLE_COLOR_1, SMALL));
    frame.tryToPlace(Circle(CIRCLE_COLOR_2, LARGE));

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
    frame.tryToPlace(Circle(CIRCLE_COLOR_1, MEDIUM));
    frame.tryToPlace(Circle(CIRCLE_COLOR_2, LARGE));

    /* Test */
    std::string expected_str = FORMATTING CIRCLE_ANSI_COLOR_2 "(";
    expected_str += CIRCLE_ANSI_COLOR_1 "( " CIRCLE_ANSI_COLOR_1 ")" CIRCLE_ANSI_COLOR_2 ")" ANSI_RESET;
    EXPECT_EQ(frame.toString(), expected_str);
}

TEST(Frame_toString, FullFrame)
{
    /* Setup */
    Frame frame = Frame();
    frame.tryToPlace(Circle(CIRCLE_COLOR_1, SMALL));
    frame.tryToPlace(Circle(CIRCLE_COLOR_2, MEDIUM));
    frame.tryToPlace(Circle(CIRCLE_COLOR_3, LARGE));

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
    frame.tryToPlace(Circle(RED, SMALL));
    std::string expected_str = FORMATTING "  " ANSI_RED "o  " ANSI_RESET;
    EXPECT_EQ(frame.toString(), expected_str);
}

TEST(Frame_toString, SmallGreenCircle)
{
    Frame frame = Frame();
    frame.tryToPlace(Circle(GREEN, SMALL));
    std::string expected_str = FORMATTING "  " ANSI_GREEN "o  " ANSI_RESET;
    EXPECT_EQ(frame.toString(), expected_str);
}

TEST(Frame_toString, SmallBlueCircle)
{
    Frame frame = Frame();
    frame.tryToPlace(Circle(BLUE, SMALL));
    std::string expected_str = FORMATTING "  " ANSI_BLUE "o  " ANSI_RESET;
    EXPECT_EQ(frame.toString(), expected_str);
}

TEST(Frame_toString, SmallOrangeCircle)
{
    Frame frame = Frame();
    frame.tryToPlace(Circle(ORANGE, SMALL));
    std::string expected_str = FORMATTING "  " ANSI_ORANGE "o  " ANSI_RESET;
    EXPECT_EQ(frame.toString(), expected_str);
}