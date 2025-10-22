#include "PawnPiece.hh"
#include "ChessBoard.hh"
using namespace Student;

PawnPiece::PawnPiece(ChessBoard &board, Color color, int row, int column) 
    : ChessPiece(board, color, row, column)
{
    type = Pawn;
}

bool PawnPiece::canMoveToLocation(int toRow, int toColumn)
{
    int dir = (color == White) ? -1 : 1;
    int startRow = (color == White) ? board.getNumRows() - 2 : 1;

    int rowDiff = toRow - row;
    int colDiff = toColumn - column;

    ChessPiece *dest = board.getPiece(toRow, toColumn);

    // Moving forward
    if (colDiff == 0)
    {
        if (dest != nullptr)
            return false;
        if (row == startRow && rowDiff == 2 * dir)
        {
            int midRow = row + dir;
            if (board.getPiece(midRow, column) == nullptr)
                return true;
        }
        if (rowDiff == dir)
            return true;
    }
    // Diagonal capture
    else if (abs(colDiff) == 1 && rowDiff == dir)
    {
        if (dest != nullptr && dest->getColor() != color)
            return true;
    }

    return false;
}

const char *PawnPiece::toString()
{
    return (color == White) ? "♙" : "♟";
}