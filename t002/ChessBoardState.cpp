#include "ChessBoardState.h"
#include "chess.h"
#include <iostream>

ChessBoardState::ChessBoardState(): isSelected(false), currentTurn(WHITE) {}

void ChessBoardState::initialize() {
    texture.loadFromFile("image/board.png");
    sprite.setTexture(texture);
    sprite.setPosition(0, 0);
    selectedRectangle.setSize(sf::Vector2f(80, 80));
    selectedRectangle.setOutlineColor(sf::Color::Green);
    print_board(board);
}

void ChessBoardState::handleInput(sf::RenderWindow &window, sf::Event &event) {
    if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
        sf::Vector2i position = sf::Mouse::getPosition(window);
        sf::Vector2f world_position = window.mapPixelToCoords(position);
        if(sprite.getGlobalBounds().contains(world_position)){
            int x = (world_position.x - sprite.getPosition().x) / 80;
            int y = (world_position.y - sprite.getPosition().y) / 80;
            if(isSelected) {
                if(std::find(validMoves.begin(), validMoves.end(), std::make_pair(y, x)) != validMoves.end()){
                    ChessPiece currentPiece = board[(int)selectedPosition.y / 80][(int)selectedPosition.x / 80];
                    ChessPiece pastPiece = {EMPTY, BLANK};
                    board[y][x] = currentPiece;
                    board[(int)selectedPosition.y / 80][(int)selectedPosition.x / 80] = pastPiece;
                    currentTurn = currentTurn == WHITE ? BLACK : WHITE;
                    print_board(board);
                }
                isSelected = false;
            }
            else{
                ChessPiece piece = board[y][x];
                if(piece.piece != EMPTY && piece.color == currentTurn) {
                    validMoves.clear();
                    switch (piece.piece) {
                        case PAWN:
                            validMoves = find_pawn_moves(board, y, x, piece.color);
                            break;
                        case ROOK:
                            validMoves = find_rook_moves(board, y, x, piece.color);
                            break;
                        case KNIGHT:
                            validMoves = find_knight_moves(board, y, x, piece.color);
                            break;
                        case BISHOP:
                            validMoves = find_bishop_moves(board, y, x, piece.color);
                            break;
                        case QUEEN:
                            validMoves = find_queen_moves(board, y, x, piece.color);
                            break;
                        case KING:
                            validMoves = find_king_moves(board, y, x, piece.color);
                            break;
                    }
                    selectedPosition.x = x * 80 + sprite.getPosition().x;
                    selectedPosition.y = y * 80 + sprite.getPosition().y;
                    selectedRectangle.setPosition(selectedPosition);
                    isSelected = true;
                }
                if(piece.piece == EMPTY || piece.color != currentTurn) isSelected = false;
            }
        }
    }
    if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape){
        isSelected = false;
    }
}

void ChessBoardState::draw(sf::RenderWindow &window) {
    window.draw(sprite);
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board[i][j].piece == EMPTY) continue;

            sf::Texture pieceTexture;
            std::string imagePath = "image/";
            if(board[i][j].color == WHITE) imagePath += "white/";
            else imagePath += "black/";

            switch (board[i][j].piece) {
                case ROOK:
                    imagePath += "rook.png";
                    break;
                case KNIGHT:
                    imagePath += "knight.png";
                    break;
                case BISHOP:
                    imagePath += "bishop.png";
                    break;
                case QUEEN:
                    imagePath += "queen.png";
                    break;
                case KING:
                    imagePath += "king.png";
                    break;
                case PAWN:
                    imagePath += "pawn.png";
                    break;
            }

            pieceTexture.loadFromFile(imagePath);
            sf::Sprite pieceSprite(pieceTexture);
            pieceSprite.setPosition(j * 80, i * 80);
            window.draw(pieceSprite);
        }
    }
    if(isSelected){
        window.draw(selectedRectangle);
        selectedRectangle.setFillColor(sf::Color::Transparent);
        selectedRectangle.setOutlineThickness(2);

        for(auto i: validMoves) {
            sf::RectangleShape moveRectangle(sf::Vector2f(80, 80));
            moveRectangle.setFillColor(sf::Color::Transparent);
            moveRectangle.setOutlineColor(sf::Color::Magenta);
            moveRectangle.setOutlineThickness(2);
            moveRectangle.setPosition(i.second * 80 + sprite.getPosition().x, i.first * 80 + sprite.getPosition().y);
            window.draw(moveRectangle);
        }


    }
}