#include "RookPiece.hh"
#include "ChessBoard.hh"
#include <cmath>
using namespace Student;

RookPiece::RookPiece(ChessBoard &board, Color color, int row, int column)
    : ChessPiece(board, color, row, column)
{
    type = Rook;
}

bool RookPiece::canMoveToLocation(int toRow, int toColumn)
{
    int rowDiff = toRow - row;
    int colDiff = toColumn - column;

    if (rowDiff != 0 && colDiff != 0)
        return false;

    int stepRow = (rowDiff == 0) ? 0 : (rowDiff > 0 ? 1 : -1);
    int stepCol = (colDiff == 0) ? 0 : (colDiff > 0 ? 1 : -1);

    int r = row + stepRow, c = column + stepCol;
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

const char *RookPiece::toString()
{
    return (color == White) ? "♖" : "♜";
}
