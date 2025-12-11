#include "KnightPiece.hh"
#include "ChessBoard.hh"
#include <cmath>

using namespace Student;

KnightPiece::KnightPiece(ChessBoard &board, Color color, int row, int column)
    : ChessPiece(board, color, row, column)
{
    type = Knight;
}

bool KnightPiece::canMoveToLocation(int toRow, int toColumn)
{
    int rowDiff = std::abs(toRow - row);
    int colDiff = std::abs(toColumn - column);

    if (!((rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2)))
        return false;

    ChessPiece *dest = board.getPiece(toRow, toColumn);
    if (dest == nullptr || dest->getColor() != color)
        return true;
    return false;
}

const char *KnightPiece::toString()
{
    return (color == White) ? "♘" : "♞";
}
