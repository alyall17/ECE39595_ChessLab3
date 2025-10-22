#include "ChessPiece.hh"
#include "ChessBoard.hh"

using namespace Student;

ChessPiece::ChessPiece(ChessBoard &board, Color color, int row, int column)
    : board(board), color(color), row(row), column(column) {}

Color ChessPiece::getColor() { return color; }
Type ChessPiece::getType() { return type; }
int ChessPiece::getRow() { return row; }
int ChessPiece::getColumn() { return column; }

void ChessPiece::setPosition(int r, int c)
{
    row = r;
    column = c;
}
