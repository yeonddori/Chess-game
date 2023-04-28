#ifndef CHESS_GAME_CHESS_H
#define CHESS_GAME_CHESS_H

#include <vector>

const int BOARD_SIZE = 8;

// Piece types
enum Piece {
    EMPTY,
    PAWN,
    ROOK,
    KNIGHT,
    BISHOP,
    QUEEN,
    KING
};

// Colors
enum Color {
    BLANK,
    WHITE,
    BLACK
};

// Struct for a chess piece
struct ChessPiece {
    Piece piece;
    Color color;
};

typedef ChessPiece ChessBoard[BOARD_SIZE][BOARD_SIZE];

/**
 * @brief Prints the chess board to the console.
 *
 * @param board The board to print.
 */
void print_board(ChessBoard const board);

/**
 * @brief Finds all the legal moves for a bishop on the chess board.
 *
 * @param board The board to search for legal moves.
 * @param x The x-coordinate of the bishop.
 * @param y The y-coordinate of the bishop.
 * @param color The color of the bishop.
 * @return A vector containing all the legal moves for the bishop.
 * @ref https://www.chess.com/lessons/how-to-move-the-pieces
 */
std::vector<std::pair<int, int>> find_bishop_moves(ChessBoard board, int x, int y, Color color) ;

/**
 * @brief Finds all the legal moves for a knight on the chess board.
 *
 * @param board The board to search for legal moves.
 * @param x The x-coordinate of the knight.
 * @param y The y-coordinate of the knight.
 * @param color The color of the knight.
 * @return A vector containing all the legal moves for the knight.
 * @ref https://www.chess.com/lessons/how-to-move-the-pieces
 */
std::vector<std::pair<int, int>> find_knight_moves(ChessBoard board, int x, int y, Color color);

/**
 * @brief Finds all the legal moves for a pawn on the chess board.
 *
 * @param board The board to search for legal moves.
 * @param x The x-coordinate of the pawn.
 * @param y The y-coordinate of the pawn.
 * @param color The color of the pawn.
 * @return A vector containing all the legal moves for the pawn.
 * @ref https://www.chess.com/lessons/how-to-move-the-pieces
 */
std::vector<std::pair<int, int>> find_pawn_moves(ChessBoard board,int x, int y, Color color);

/**
 * @brief Finds all the legal moves for a rook on the chess board.
 *
 * @param board The board to search for legal moves.
 * @param y The y-coordinate of the rook.
 * @param x The x-coordinate of the rook.
 * @param color The color of the rook.
 * @return A vector containing all the legal moves for the rook.
 * @ref https://www.chess.com/lessons/how-to-move-the-pieces
 */
std::vector<std::pair<int, int>> find_rook_moves(ChessBoard board,int x, int y, Color color);

/**
 * @brief Finds all the legal moves for a queen on the chess board.
 *
 * @param board The board to search for legal moves.
 * @param y The y-coordinate of the queen.
 * @param x The x-coordinate of the queen.
 * @param color The color of the queen.
 * @return A vector containing all the legal moves for the queen.
 * @ref https://www.chess.com/lessons/how-to-move-the-pieces
 */
std::vector<std::pair<int, int>> find_queen_moves(ChessBoard board, int x, int y, Color color);

/**
 * @brief Finds all the legal moves for a king on the chess board.
 *
 * @param board The board to search for legal moves.
 * @param y The y-coordinate of the king.
 * @param x The x-coordinate of the king.
 * @param color The color of the king.
 * @return A vector containing all the legal moves for the king.
 * @ref https://www.chess.com/lessons/how-to-move-the-pieces
 */
std::vector<std::pair<int, int>> find_king_moves(ChessBoard board, int x, int y, Color color);
#endif //CHESS_GAME_CHESS_H