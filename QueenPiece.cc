#include "QueenPiece.hh"
#include "ChessBoard.hh"
#include <cmath>

using namespace Student;

QueenPiece::QueenPiece(ChessBoard &board, Color color, int row, int column)
    : ChessPiece(board, color, row, column)
{
    type = Queen;
}

bool QueenPiece::canMoveToLocation(int toRow, int toColumn)
{
    int rowDiff = toRow - row;
    int colDiff = toColumn - column;

    if (rowDiff == 0 && colDiff == 0)
        return false;

    int absRow = std::abs(rowDiff);
    int absCol = std::abs(colDiff);

    int stepRow = 0;
    int stepCol = 0;

    if (rowDiff == 0 && colDiff != 0)
    {
        stepRow = 0;
        stepCol = (colDiff > 0) ? 1 : -1;
    }
    else if (colDiff == 0 && rowDiff != 0)
    {
        stepCol = 0;
        stepRow = (rowDiff > 0) ? 1 : -1;
    }
    
    else if (absRow == absCol)
    {
        stepRow = (rowDiff > 0) ? 1 : -1;
        stepCol = (colDiff > 0) ? 1 : -1;
    }
    else
    {
        return false;
    }

    int r = row + stepRow;
    int c = column + stepCol;
    while (r != toRow || c != toColumn)
    {
        if (board.getPiece(r, c) != nullptr)
            return false;
        r += stepRow;
        c += stepCol;
    }

    ChessPiece *dest = board.getPiece(toRow, toColumn);
    if (dest == nullptr || dest->getColor() != color)
        return true;

    return false;
}

const char *QueenPiece::toString()
{
    return (color == White) ? "♕" : "♛";
}
