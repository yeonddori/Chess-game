#ifndef CHESS_GAME_CHESSPIECE_H
#define CHESS_GAME_CHESSPIECE_H

class ChessPiece {
public:
    enum Piece {
        EMPTY,
        PAWN,
        ROOK,
        KNIGHT,
        BISHOP,
        QUEEN,
        KING
    };
    enum Color {
        BLANK,
        WHITE,
        BLACK
    };
    ChessPiece(ChessPiece::Piece piece, ChessPiece::Color color);
    Piece getPiece() const;
    Color getColor() const;
private:
    Piece piece;
    Color color;
};

#endif //CHESS_GAME_CHESSPIECE_H
