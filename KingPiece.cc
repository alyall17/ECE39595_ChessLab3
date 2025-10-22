// KingPiece.cc
#include "KingPiece.hh"
#include "ChessBoard.hh"
#include <cmath>

using namespace Student;

KingPiece::KingPiece(ChessBoard &board, Color color, int row, int column)
    : ChessPiece(board, color, row, column)
{
    type = King;
}

bool KingPiece::canMoveToLocation(int toRow, int toColumn)
{
    // Basic bounds check (ChessBoard::getNumRows/getNumCols exist)
    if (toRow < 0 || toRow >= board.getNumRows()) return false;
    if (toColumn < 0 || toColumn >= board.getNumCols()) return false;

    // Can't stay in same place
    if (toRow == row && toColumn == column) return false;

    int dr = std::abs(toRow - row);
    int dc = std::abs(toColumn - column);

    // King moves one square in any direction
    if (dr <= 1 && dc <= 1) {
        // Destination may be empty or an opponent piece.
        ChessPiece *dest = board.getPiece(toRow, toColumn);
        if (dest == nullptr) return true;
        return dest->getColor() != color;
    }

    return false;
}

const char *KingPiece::toString()
{
    return (color == White) ? "♔" : "♚";
}
