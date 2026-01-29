#include <gtest/gtest.h>
#include "ANSI.hpp"
#include "Board.hpp"

#define FRAME_FORMATTING ANSI_BOLD

TEST(Board_constructor, framesAreEmptyAtInit)
{
    /* Setup */
    Board board = Board();

    /* Test */
    std::array<std::array<Frame, 3>, 3> frames = board.getFrames();
    for (int y = 0; y < BOARD_SIZE; y++)
    {
        for (int x = 0; x < BOARD_SIZE; x++)
        {
            Frame &frame = frames[x][y];
            EXPECT_EQ(frame.getCircle(SMALL), nullptr);
            EXPECT_EQ(frame.getCircle(MEDIUM), nullptr);
            EXPECT_EQ(frame.getCircle(LARGE), nullptr);
        }
    }
}

TEST(Board_toString, emptyBoard)
{
    /* Setup */
    Board emptyBoard = Board();
    std::string expected = "     1     2     3  \n"
                           "  ┌─────┬─────┬─────┐\n"
                           "A │[1m     [0m│[1m     [0m│[1m     [0m│\n"
                           "  ├─────┼─────┼─────┤\n"
                           "B │[1m     [0m│[1m     [0m│[1m     [0m│\n"
                           "  ├─────┼─────┼─────┤\n"
                           "C │[1m     [0m│[1m     [0m│[1m     [0m│\n"
                           "  └─────┴─────┴─────┘\n";

    /* Test */
    EXPECT_EQ(emptyBoard.toString(), expected);
}
