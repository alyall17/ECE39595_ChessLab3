#include "ChessBoard.hh"
#include "PawnPiece.hh"
#include "RookPiece.hh"
#include "BishopPiece.hh"
#include "KingPiece.hh"

using Student::ChessBoard;

ChessBoard::ChessBoard(int numRow, int numCol)
{
    numRows = numRow;
    numCols = numCol;
    board = std::vector<std::vector<ChessPiece *>>(numRows, std::vector<ChessPiece *>(numCols, nullptr));
}

void ChessBoard::createChessPiece(Color col, Type ty, int startRow, int startColumn)
{
    // Remove existing piece
    if (board.at(startRow).at(startColumn) != nullptr)
    {
        delete board.at(startRow).at(startColumn);
    }

    ChessPiece *piece = nullptr;
    switch (ty)
    {
    case Pawn:
        piece = new PawnPiece(*this, col, startRow, startColumn);
        break;
    case Rook:
        piece = new RookPiece(*this, col, startRow, startColumn);
        break;
    case Bishop:
        piece = new BishopPiece(*this, col, startRow, startColumn);
        break;
    case King:
        piece = new KingPiece(*this, col, startRow, startColumn);
        break;
    }

    board.at(startRow).at(startColumn) = piece;
}

bool ChessBoard::isValidMove(int fromRow, int fromColumn, int toRow, int toColumn)
{
    if (fromRow < 0 || fromRow >= numRows || fromColumn < 0 || fromColumn >= numCols)
        return false;
    if (toRow < 0 || toRow >= numRows || toColumn < 0 || toColumn >= numCols)
        return false;

    ChessPiece *piece = board.at(fromRow).at(fromColumn);
    if (piece == nullptr)
        return false;

    // Same spot
    if (fromRow == toRow && fromColumn == toColumn)
        return false;

    return piece->canMoveToLocation(toRow, toColumn);
}

// Dummy placeholders for Part 1
bool ChessBoard::movePiece(int, int, int, int) { return false; }
bool ChessBoard::isPieceUnderThreat(int, int) { return false; }

std::ostringstream ChessBoard::displayBoard()
{
    std::ostringstream outputString;
    // top scale
    outputString << "  ";
    for (int i = 0; i < numCols; i++){
        outputString << i << " ";
    }
    outputString << std::endl << "  ";
    // top border
    for (int i = 0; i < numCols; i++){
        outputString << "– ";
    }
    outputString << std::endl;

    for (int row = 0; row < numRows; row++){
        outputString << row << "|";
        for (int column = 0; column < numCols; column++){
            ChessPiece *piece = board.at(row).at(column);
            outputString << (piece == nullptr ? " " : piece->toString()) << " ";
        }
        outputString << "|" << std::endl;
    }

    // bottom border
    outputString << "  ";
    for (int i = 0; i < numCols; i++){
        outputString << "– ";
    }
    outputString << std::endl << std::endl;

    return outputString;
}

ChessBoard::~ChessBoard()
{
    for (int r = 0; r < numRows; r++)
    {
        for (int c = 0; c < numCols; c++)
        {
            delete board[r][c];  // safely deletes nullptr too
        }
    }
}