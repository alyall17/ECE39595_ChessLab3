#include "BishopPiece.hh"
#include "ChessBoard.hh"
#include <cmath>
using namespace Student;

BishopPiece::BishopPiece(ChessBoard &board, Color color, int row, int column) : ChessPiece(board, color, row, column)
{
    type = Bishop;
}

bool BishopPiece::canMoveToLocation(int toRow, int toColumn)
{
    int rowDiff = toRow - row;
    int colDiff = toColumn - column;

    if (abs(rowDiff) != abs(colDiff))
        return false;

    int stepRow = (rowDiff > 0) ? 1 : -1;
    int stepCol = (colDiff > 0) ? 1 : -1;
    int r = row + stepRow;
    int c = column + stepCol;

    while (r != toRow && c != toColumn)
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

const char *BishopPiece::toString()
{
    return (color == White) ? "♗" : "♝";
}
