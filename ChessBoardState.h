#ifndef CHESS_GAME_CHESSBOARDSTATE_H
#define CHESS_GAME_CHESSBOARDSTATE_H

#include <SFML/Graphics.hpp>
#include "ChessPiece.h"

const int BOARD_SIZE = 8;

class ChessBoardState{
public:
    ChessBoardState();
    void initialize();
    void handleInput(sf::RenderWindow& window, sf::Event& event);
    void draw(sf::RenderWindow& window);
    void print_board();
    std::vector<std::pair<int, int>> find_bishop_moves(int x, int y, ChessPiece::Color color) ;
    std::vector<std::pair<int, int>> find_knight_moves(int x, int y, ChessPiece::Color color);
    std::vector<std::pair<int, int>> find_pawn_moves(int x, int y, ChessPiece::Color color);
    std::vector<std::pair<int, int>> find_rook_moves(int x, int y, ChessPiece::Color color);
    std::vector<std::pair<int, int>> find_queen_moves(int x, int y, ChessPiece::Color color);
    std::vector<std::pair<int, int>> find_king_moves(int x, int y, ChessPiece::Color color);
private:
    sf::Texture texture;
    sf::Sprite sprite;
    sf::RectangleShape selectedRectangle;
    bool isSelected;
    sf::Vector2f selectedPosition;
    std::vector<std::pair<int, int>> validMoves;
    ChessPiece::Color currentTurn;
    std::vector<std::vector<std::unique_ptr<ChessPiece>>> board;
};
#endif //CHESS_GAME_CHESSBOARDSTATE_H
