#include "ChessPiece.h"

ChessPiece::ChessPiece(ChessPiece::Piece piece, ChessPiece::Color color)
    : piece(piece), color(color) {}
ChessPiece::Piece ChessPiece::getPiece() const {
    return piece;
}
ChessPiece::Color ChessPiece::getColor() const {
    return color;
}