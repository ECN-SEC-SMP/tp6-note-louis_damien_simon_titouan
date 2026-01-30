#include <stdexcept>
#include "Board.hpp"

#define ROW_LABEL_MARGIN "  "

/* Constructors ------------------------------------------------------------- */

Board::Board() = default;

Board::~Board() = default;

/* Getters ------------------------------------------------------------------ */

std::array<std::array<Frame, 3>, 3> &Board::getFrames()
{
    return this->frames;
}

/* Methods ------------------------------------------------------------------ */

std::string Board::toString() const
{
    std::string outputString;
    std::string rowLabels[BOARD_SIZE] = {"1", "2", "3"};
    std::string columnLabels[BOARD_SIZE] = {"A", "B", "C"};

    /* Add column labels to output string */
    outputString += ROW_LABEL_MARGIN;
    for (int columnIdx = 0; columnIdx < BOARD_SIZE; columnIdx++)
    {
        outputString += "   "; // center label
        outputString += columnLabels[columnIdx];
        outputString += "  "; // fill until next separator
    }
    outputString += "\n";

    /* Iterate over board rows (top to bottom) */
    for (int y = 0; y < BOARD_SIZE; y++)
    {
        /* For each line, create two strings:
            - separators: it contains the top separators of the line (horizontal separators)
            - contents: it contains the vertical separators, the frames content and the row labels
        */
        std::string separators = "";
        std::string contents = "";

        /* Add row label */
        separators += ROW_LABEL_MARGIN;
        contents += rowLabels[y] + " ";

        /* Iterate over columns (left to right) */
        for (int x = 0; x < BOARD_SIZE; x++)
        {
            /* For each frame, add strings for:
                - top separator and top left corner (separators):
                    ╔═════+
                    ¦     ¦
                    +-----+
                - left separator and content of the frame (contents):
                    +-----+
                    ║XXXXX¦
                    +-----+
            */
            separators += this->computeGridNode(x, y);
            separators += this->boardStyle.horizontalSeparator;

            contents += this->boardStyle.verticalSeparator;
            contents += this->frames[x][y].toString();

            /* Right border */
            if (x == BOARD_SIZE - 1)
            {
                separators += this->computeGridNode(x + 1, y);
                contents += this->boardStyle.verticalSeparator;
            }
        }

        /* Add frame top separator and frame content to output string */
        outputString += separators + "\n";
        outputString += contents + "\n";
    }

    /* Bottom border */
    std::string separators = ROW_LABEL_MARGIN;
    for (int x = 0; x < BOARD_SIZE; x++)
    {
        separators += this->computeGridNode(x, BOARD_SIZE);
        separators += this->boardStyle.horizontalSeparator;
    }

    /* Bottom right corner */
    separators += this->computeGridNode(BOARD_SIZE, BOARD_SIZE);

    /* Add bottom border */
    outputString += separators + "\n";

    return outputString;
}

int Board::axisIndexFromCoord(int coord) const
{
    /** Axis index returned:
     * 0 = start
     * 1 = middle
     * 2 = end
     */
    if (coord == 0)
        return 0;
    else if (coord > 0 and coord < BOARD_SIZE)
        return 1;
    else if (coord == BOARD_SIZE)
        return 2;
    else
        throw std::invalid_argument("coord must be in the range {0," + std::to_string(BOARD_SIZE) + "}");
}

std::string Board::computeGridNode(int x, int y) const
{
    int xIndex = this->axisIndexFromCoord(x);
    int yIndex = this->axisIndexFromCoord(y);

    const std::string *nodesTable[3][3] = {
        {&boardStyle.node_top_left, &boardStyle.node_top, &boardStyle.node_top_right},
        {&boardStyle.node_left, &boardStyle.node_middle, &boardStyle.node_right},
        {&boardStyle.node_bottom_left, &boardStyle.node_bottom, &boardStyle.node_bottom_right}};

    return *nodesTable[yIndex][xIndex];
}