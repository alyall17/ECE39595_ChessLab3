#include "ChessBoard.hh"
#include "PawnPiece.hh"
#include "RookPiece.hh"
#include "BishopPiece.hh"
#include "KingPiece.hh"
#include "KnightPiece.hh"
#include "QueenPiece.hh"

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
    case Knight:
        piece = new KnightPiece(*this, col, startRow, startColumn);
        break;
    case Queen:
        piece = new QueenPiece(*this, col, startRow, startColumn);
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

    // Basic movement rules (per-piece)
    if (!piece->canMoveToLocation(toRow, toColumn))
        return false;

    Color moverColor = piece->getColor();

    ChessPiece *captured = board.at(toRow).at(toColumn);

    // perform move temporarily
    board.at(toRow).at(toColumn) = piece;
    board.at(fromRow).at(fromColumn) = nullptr;
    int oldRow = piece->getRow();
    int oldCol = piece->getColumn();
    piece->setPosition(toRow, toColumn);

    // find king of moverColor
    int kingRow = -1, kingCol = -1;
    for (int r = 0; r < numRows; ++r)
    {
        for (int c = 0; c < numCols; ++c)
        {
            ChessPiece *p = board.at(r).at(c);
            if (p != nullptr && p->getColor() == moverColor && p->getType() == King)
            {
                kingRow = r;
                kingCol = c;
                break;
            }
        }
        if (kingRow != -1) break;
    }

    bool kingInCheck = false;
    if (kingRow != -1 && kingCol != -1)
    {
        kingInCheck = isPieceUnderThreat(kingRow, kingCol);
    }

    // revert simulation
    board.at(fromRow).at(fromColumn) = piece;
    board.at(toRow).at(toColumn) = captured;
    piece->setPosition(oldRow, oldCol);

    return !kingInCheck;
}

// Dummy placeholders for Part 1 - START part 2 implementation - EDITED for part 3
bool ChessBoard::movePiece(int fromRow, int fromColumn, int toRow, int toColumn)
{
    if (fromRow < 0 || fromRow >= numRows || fromColumn < 0 || fromColumn >= numCols)
        return false;
    if (toRow < 0 || toRow >= numRows || toColumn < 0 || toColumn >= numCols)
        return false;

    ChessPiece *piece = board.at(fromRow).at(fromColumn);
    if (piece == nullptr)
        return false;

    if (piece->getColor() != turn)
        return false;

    if (!isValidMove(fromRow, fromColumn, toRow, toColumn))
        return false;

    //Part 3
    Color moverColor = piece->getColor();
    ChessPiece *captured = board.at(toRow).at(toColumn);
    bool enPassantCapture = false;
    ChessPiece *epCaptured = nullptr;

    if (piece->getType() == Pawn && fromColumn != toColumn && captured == nullptr) {
        ChessPiece *possible = board.at(fromRow).at(toColumn);
        if (possible != nullptr && possible->getType() == Pawn && possible->getColor() != moverColor) {
            if (lastToRow == possible->getRow() && lastToCol == possible->getColumn() && std::abs(lastFromRow - lastToRow) == 2) {
                enPassantCapture = true;
                epCaptured = possible;
            }
        }
    }

    board.at(toRow).at(toColumn) = piece;
    board.at(fromRow).at(fromColumn) = nullptr;
    piece->setPosition(toRow, toColumn);

    int kingRow = -1;
    int kingCol = -1;
    for (int r = 0; r < numRows; ++r)
    {
        for (int c = 0; c < numCols; ++c)
        {
            ChessPiece *p = board.at(r).at(c);
            if (p != nullptr && p->getColor() == moverColor && p->getType() == King)
            {
                kingRow = r;
                kingCol = c;
                break;
            }
        }
        if (kingRow != -1)
            break;
    }

    bool kingInCheck = false;
    if (kingRow != -1 && kingCol != -1)
    {
        kingInCheck = isPieceUnderThreat(kingRow, kingCol);
    }

    if (kingInCheck)
    {
        board.at(fromRow).at(fromColumn) = piece;
        board.at(toRow).at(toColumn) = captured;
        piece->setPosition(fromRow, fromColumn);
        return false;
    }

    if (captured != nullptr)
    {
        delete captured;
        captured = nullptr;
    }
    if (enPassantCapture && epCaptured != nullptr) {
        delete epCaptured;
        board.at(fromRow).at(toColumn) = nullptr;
        epCaptured = nullptr;
    }

    if (piece->getType() == King && std::abs(toColumn - fromColumn) == 2) {
        int rookFromCol = (toColumn > fromColumn) ? (numCols - 1) : 0;
        int rookToCol = (toColumn > fromColumn) ? (toColumn - 1) : (toColumn + 1);
        ChessPiece *rook = board.at(fromRow).at(rookFromCol);
        if (rook != nullptr && rook->getType() == Rook && rook->getColor() == moverColor) {
            board.at(fromRow).at(rookToCol) = rook;
            board.at(fromRow).at(rookFromCol) = nullptr;
            rook->setPosition(fromRow, rookToCol);
            rook->setHasMoved(true);
        }
    }

    if (piece->getType() == Pawn) {
        if ((piece->getColor() == White && toRow == 0) || (piece->getColor() == Black && toRow == numRows - 1)) {
            board.at(toRow).at(toColumn) = nullptr;
            delete piece;
            ChessPiece *promo = new QueenPiece(*this, moverColor, toRow, toColumn);
            board.at(toRow).at(toColumn) = promo;
            promo->setHasMoved(true);
        }
    }

    lastFromRow = fromRow; lastFromCol = fromColumn; lastToRow = toRow; lastToCol = toColumn; lastMoveType = piece->getType(); lastMoveColor = moverColor;

    turn = (turn == White ? Black : White);
    piece->setHasMoved(true);
    return true;
}


bool ChessBoard::isPieceUnderThreat(int row, int column)
{
    ChessPiece* target = nullptr;
    if (row >= 0 && row < numRows && column >= 0 && column < numCols) {
        target = board.at(row).at(column);
    }
    if (target == nullptr) return false;

    Color defender = target->getColor();
    return isSquareUnderAttack(row, column, defender);
}

bool ChessBoard::isSquareUnderAttack(int row, int column, Color defenderColor)
{
    if (row < 0 || row >= numRows || column < 0 || column >= numCols) return false;
    for (int r = 0; r < numRows; ++r) {
        for (int c = 0; c < numCols; ++c) {
            ChessPiece* attacker = board.at(r).at(c);
            if (attacker == nullptr) continue;
            if (attacker->getColor() == defenderColor) continue;
            if (attacker->canMoveToLocation(row, column)) {
                return true;
            }
        }
    }
    return false;
}

float ChessBoard::scoreBoard()
{
    // piece values
    auto pieceValue = [](Type t) -> int {
        switch (t) {
        case King: return 200;
        case Queen: return 9;
        case Rook: return 5;
        case Knight: return 3;
        case Bishop: return 3;
        case Pawn: return 1;
        default: return 0;
        }
    };

    Color me = turn;
    Color opp = (turn == White) ? Black : White;

    int myMaterial = 0;
    int oppMaterial = 0;
    int myMoves = 0;
    int oppMoves = 0;

    for (int r = 0; r < numRows; ++r) {
        for (int c = 0; c < numCols; ++c) {
            ChessPiece* p = board.at(r).at(c);
            if (p == nullptr) continue;
            if (p->getColor() == me) {
                myMaterial += pieceValue(p->getType());
                for (int tr = 0; tr < numRows; ++tr) for (int tc = 0; tc < numCols; ++tc) if (isValidMove(r,c,tr,tc)) ++myMoves;
            } else {
                oppMaterial += pieceValue(p->getType());
                for (int tr = 0; tr < numRows; ++tr) for (int tc = 0; tc < numCols; ++tc) if (isValidMove(r,c,tr,tc)) ++oppMoves;
            }
        }
    }

    float score = (float)myMaterial + 0.1f * (float)myMoves - ((float)oppMaterial + 0.1f * (float)oppMoves);
    return score;
}

float ChessBoard::getHighestNextScore()
{
    float best = -1e9f;
    // iterate all pieces
    for (int r = 0; r < numRows; ++r) {
        for (int c = 0; c < numCols; ++c) {
            ChessPiece *p = board.at(r).at(c);
            if (p == nullptr || p->getColor() != turn) continue;
            for (int tr = 0; tr < numRows; ++tr) {
                for (int tc = 0; tc < numCols; ++tc) {
                    if (!isValidMove(r,c,tr,tc)) continue;

                    ChessBoard *tmp = new ChessBoard(numRows, numCols);
                    for (int rr = 0; rr < numRows; ++rr) {
                        for (int cc = 0; cc < numCols; ++cc) {
                            ChessPiece *pp = board.at(rr).at(cc);
                            if (pp == nullptr) continue;
                            tmp->createChessPiece(pp->getColor(), pp->getType(), rr, cc);
                            ChessPiece *qq = tmp->getPiece(rr, cc);
                            if (qq) qq->setHasMoved(pp->hasMoved());
                        }
                    }
                    tmp->lastFromRow = lastFromRow;
                    tmp->lastFromCol = lastFromCol;
                    tmp->lastToRow = lastToRow;
                    tmp->lastToCol = lastToCol;
                    tmp->lastMoveType = lastMoveType;
                    tmp->lastMoveColor = lastMoveColor;
                    tmp->turn = turn;

                    bool ok = tmp->movePiece(r,c,tr,tc);
                    if (ok) {
                        
                        tmp->turn = p->getColor();
                        float sc = tmp->scoreBoard();
                        if (sc > best) best = sc;
                    }
                    delete tmp;
                }
            }
        }
    }
    if (best == -1e9f) return scoreBoard();
    return best;
}
//Part 2 implementation END

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

bool ChessBoard::isInCheck(Color color)
{
    int kingRow = -1, kingCol = -1;
    for (int r = 0; r < numRows; ++r) {
        for (int c = 0; c < numCols; ++c) {
            ChessPiece *p = board.at(r).at(c);
            if (p != nullptr && p->getColor() == color && p->getType() == King) {
                kingRow = r; kingCol = c; break;
            }
        }
        if (kingRow != -1) break;
    }
    if (kingRow == -1) return false;
    return isSquareUnderAttack(kingRow, kingCol, color);
}

bool ChessBoard::isCheckmate(Color color)
{
    if (!isInCheck(color)) return false;


    for (int r = 0; r < numRows; ++r) {
        for (int c = 0; c < numCols; ++c) {
            ChessPiece *p = board.at(r).at(c);
            if (p == nullptr || p->getColor() != color) continue;
            for (int tr = 0; tr < numRows; ++tr) {
                for (int tc = 0; tc < numCols; ++tc) {
                    if (isValidMove(r, c, tr, tc)) return false;
                }
            }
        }
    }
    return true;
}

bool ChessBoard::isEnPassantCapture(int fromRow, int fromCol, int toRow, int toCol, Color moverColor)
{
    if (fromRow < 0 || fromRow >= numRows) return false;
    if (toRow < 0 || toRow >= numRows) return false;
    if (fromCol < 0 || fromCol >= numCols) return false;
    if (toCol < 0 || toCol >= numCols) return false;

    ChessPiece* dest = board.at(toRow).at(toCol);
    if (dest != nullptr) return false; 

    ChessPiece* possible = board.at(fromRow).at(toCol);
    if (possible == nullptr) return false;
    if (possible->getType() != Pawn) return false;
    if (possible->getColor() == moverColor) return false;

    if (lastMoveType != Pawn) return false;
    if (lastMoveColor == moverColor) return false;
    if (lastToRow == possible->getRow() && lastToCol == possible->getColumn() && std::abs(lastFromRow - lastToRow) == 2) {
        return true;
    }
    return false;
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