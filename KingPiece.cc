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
    if (toRow < 0 || toRow >= board.getNumRows()) return false;
    if (toColumn < 0 || toColumn >= board.getNumCols()) return false;

    if (toRow == row && toColumn == column) return false;

    int dr = std::abs(toRow - row);
    int dc = std::abs(toColumn - column);

    if (dr <= 1 && dc <= 1) {
        ChessPiece *dest = board.getPiece(toRow, toColumn);
        if (dest == nullptr) return true;
        return dest->getColor() != color;
    }
 //castle
    if (dr == 0 && dc == 2) {
        if (this->hasMoved()) return false;

        int dir = (toColumn > column) ? 1 : -1;
        int rookCol = (dir == 1) ? board.getNumCols() - 1 : 0;
        ChessPiece *rook = board.getPiece(row, rookCol);
        if (rook == nullptr || rook->getType() != Rook || rook->getColor() != color) return false;
        if (rook->hasMoved()) return false;

        if (board.isSquareUnderAttack(row, column, color)) return false;

        int c = column + dir;
        while (c != rookCol) {
            if (board.getPiece(row, c) != nullptr && c != toColumn) return false;
            if (board.isSquareUnderAttack(row, c, color)) return false;
            c += dir;
        }

        return true;
    }

    return false;
}

const char *KingPiece::toString()
{
    return (color == White) ? "♔" : "♚";
}
