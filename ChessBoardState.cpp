#include "ChessBoardState.h"
#include <iostream>

ChessBoardState::ChessBoardState(): isSelected(false), currentTurn(ChessPiece::Color::WHITE) {
    board.resize(BOARD_SIZE);
    for (int i=0; i<BOARD_SIZE; i++) {
        board[i].resize(BOARD_SIZE);
    }

    board[0][0] = std::make_unique<ChessPiece>(ChessPiece::Piece::ROOK, ChessPiece::Color::BLACK);
    board[0][1] = std::make_unique<ChessPiece>(ChessPiece::Piece::KNIGHT, ChessPiece::Color::BLACK);
    board[0][2] = std::make_unique<ChessPiece>(ChessPiece::Piece::BISHOP, ChessPiece::Color::BLACK);
    board[0][3] = std::make_unique<ChessPiece>(ChessPiece::Piece::QUEEN, ChessPiece::Color::BLACK);
    board[0][4] = std::make_unique<ChessPiece>(ChessPiece::Piece::KING, ChessPiece::Color::BLACK);
    board[0][5] = std::make_unique<ChessPiece>(ChessPiece::Piece::BISHOP, ChessPiece::Color::BLACK);
    board[0][6] = std::make_unique<ChessPiece>(ChessPiece::Piece::KNIGHT, ChessPiece::Color::BLACK);
    board[0][7] = std::make_unique<ChessPiece>(ChessPiece::Piece::ROOK, ChessPiece::Color::BLACK);

    for(int i=0; i<8; i++) board[1][i] = std::make_unique<ChessPiece>(ChessPiece::Piece::PAWN, ChessPiece::Color::BLACK);

    for(int i=2; i<=5; i++) {
        for (int j = 0; j < 8; j++)
            board[i][j] = std::make_unique<ChessPiece>(ChessPiece::Piece::EMPTY, ChessPiece::Color::BLANK);
    }

    for(int i=0; i<8; i++) board[6][i] = std::make_unique<ChessPiece>(ChessPiece::Piece::PAWN, ChessPiece::Color::WHITE);

    board[7][0] = std::make_unique<ChessPiece>(ChessPiece::Piece::ROOK, ChessPiece::Color::WHITE);
    board[7][1] = std::make_unique<ChessPiece>(ChessPiece::Piece::KNIGHT, ChessPiece::Color::WHITE);
    board[7][2] = std::make_unique<ChessPiece>(ChessPiece::Piece::BISHOP, ChessPiece::Color::WHITE);
    board[7][3] = std::make_unique<ChessPiece>(ChessPiece::Piece::QUEEN, ChessPiece::Color::WHITE);
    board[7][4] = std::make_unique<ChessPiece>(ChessPiece::Piece::KING, ChessPiece::Color::WHITE);
    board[7][5] = std::make_unique<ChessPiece>(ChessPiece::Piece::BISHOP, ChessPiece::Color::WHITE);
    board[7][6] = std::make_unique<ChessPiece>(ChessPiece::Piece::KNIGHT, ChessPiece::Color::WHITE);
    board[7][7] = std::make_unique<ChessPiece>(ChessPiece::Piece::ROOK, ChessPiece::Color::WHITE);
}

void ChessBoardState::initialize() {
    texture.loadFromFile("image/board.png");
    sprite.setTexture(texture);
    sprite.setPosition(0, 0);
    selectedRectangle.setSize(sf::Vector2f(80, 80));
    selectedRectangle.setOutlineColor(sf::Color::Green);
    print_board();
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
                    ChessPiece currentPiece = {board[(int)selectedPosition.y / 80][(int)selectedPosition.x / 80]->getPiece(), board[(int)selectedPosition.y / 80][(int)selectedPosition.x / 80]->getColor()};
                    ChessPiece pastPiece = {ChessPiece::Piece::EMPTY, ChessPiece::Color::BLANK};
                    board[y][x] = std::make_unique<ChessPiece>(currentPiece);
                    board[(int)selectedPosition.y / 80][(int)selectedPosition.x / 80] = std::make_unique<ChessPiece>(pastPiece);
                    currentTurn = currentTurn == ChessPiece::Color::WHITE ? ChessPiece::Color::BLACK : ChessPiece::Color::WHITE;
                    print_board();
                }
                isSelected = false;
            }
            else{
                ChessPiece piece = {board[y][x]->getPiece(), board[y][x]->getColor()};
                if(piece.getPiece() != ChessPiece::Piece::EMPTY && piece.getColor() == currentTurn) {
                    validMoves.clear();
                    switch (piece.getPiece()) {
                        case ChessPiece::Piece::PAWN:
                            validMoves = find_pawn_moves(y, x, piece.getColor());
                            break;
                        case ChessPiece::Piece::ROOK:
                            validMoves = find_rook_moves(y, x, piece.getColor());
                            break;
                        case ChessPiece::Piece::KNIGHT:
                            validMoves = find_knight_moves(y, x, piece.getColor());
                            break;
                        case ChessPiece::Piece::BISHOP:
                            validMoves = find_bishop_moves(y, x, piece.getColor());
                            break;
                        case ChessPiece::Piece::QUEEN:
                            validMoves = find_queen_moves(y, x, piece.getColor());
                            break;
                        case ChessPiece::Piece::KING:
                            validMoves = find_king_moves(y, x, piece.getColor());
                            break;
                    }
                    selectedPosition.x = x * 80 + sprite.getPosition().x;
                    selectedPosition.y = y * 80 + sprite.getPosition().y;
                    selectedRectangle.setPosition(selectedPosition);
                    isSelected = true;
                }
                if(piece.getPiece() == ChessPiece::Piece::EMPTY || piece.getColor() != currentTurn) isSelected = false;
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
            if (board[i][j]->getPiece() == ChessPiece::Piece::EMPTY) continue;

            sf::Texture pieceTexture;
            std::string imagePath = "image/";
            if(board[i][j]->getColor() == ChessPiece::Color::WHITE) imagePath += "white/";
            else imagePath += "black/";

            switch (board[i][j]->getPiece()) {
                case ChessPiece::Piece::ROOK:
                    imagePath += "rook.png";
                    break;
                case ChessPiece::Piece::KNIGHT:
                    imagePath += "knight.png";
                    break;
                case ChessPiece::Piece::BISHOP:
                    imagePath += "bishop.png";
                    break;
                case ChessPiece::Piece::QUEEN:
                    imagePath += "queen.png";
                    break;
                case ChessPiece::Piece::KING:
                    imagePath += "king.png";
                    break;
                case ChessPiece::Piece::PAWN:
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

void ChessBoardState::print_board() {
    std::cout << "  0  1  2  3  4  5  6  7" << std::endl;
    for(int i=0; i<BOARD_SIZE; i++){
        std::cout << i << " ";
        for(int j=0; j<BOARD_SIZE; j++){
            ChessPiece piece = {board[i][j]->getPiece(), board[i][j]->getColor()};
            switch(piece.getPiece()){
                case ChessPiece::Piece::EMPTY:  std::cout << "   "; break;
                case ChessPiece::Piece::PAWN:   std::cout << (piece.getColor() == ChessPiece::Color::WHITE ? "Pw " : "Pb "); break;
                case ChessPiece::Piece::ROOK:   std::cout << (piece.getColor() == ChessPiece::Color::WHITE ? "Rw " : "Rb "); break;
                case ChessPiece::Piece::KNIGHT: std::cout << (piece.getColor() == ChessPiece::Color::WHITE ? "Nw " : "Nb "); break;
                case ChessPiece::Piece::BISHOP: std::cout << (piece.getColor() == ChessPiece::Color::WHITE ? "Bw " : "Bb "); break;
                case ChessPiece::Piece::QUEEN:  std::cout << (piece.getColor() == ChessPiece::Color::WHITE ? "Qw " : "Qb "); break;
                case ChessPiece::Piece::KING:   std::cout << (piece.getColor() == ChessPiece::Color::WHITE ? "Kw " : "Kb "); break;
            }
        }
        std::cout << std::endl;
    }
}

std::vector<std::pair<int, int>> ChessBoardState::find_bishop_moves(int x, int y, ChessPiece::Color color) {
    std::vector<std::pair<int, int>> moves;

    int ru=1;
    while(x-ru >= 0 && y+ru <= 7){
        ChessPiece piece = {board[x-ru][y+ru]->getPiece(), board[x-ru][y+ru]->getColor()};
        if(piece.getPiece() == ChessPiece::Piece::EMPTY){
            moves.emplace_back(x-ru, y+ru);
            ru++;
        }
        else if(piece.getPiece() != ChessPiece::Piece::EMPTY && piece.getColor() != color){
            moves.emplace_back(x-ru, y+ru);
            break;
        }
        else break;
    }

    int lu=1;
    while(x-lu >= 0 && y-lu >= 0){
        ChessPiece piece = {board[x-lu][y-lu]->getPiece(), board[x-lu][y-lu]->getColor()};
        if(piece.getPiece() == ChessPiece::Piece::EMPTY){
            moves.emplace_back(x-lu, y-lu);
            lu++;
        }
        else if(piece.getPiece() != ChessPiece::Piece::EMPTY && piece.getColor() != color){
            moves.emplace_back(x-lu, y-lu);
            break;
        }
        else break;
    }

    int rd=1;
    while(x+rd <= 7 && y+rd <= 7){
        ChessPiece piece = {board[x+rd][y+rd]->getPiece(), board[x+rd][y+rd]->getColor()};
        if(piece.getPiece() == ChessPiece::Piece::EMPTY){
            moves.emplace_back(x+rd, y+rd);
            rd++;
        }
        else if(piece.getPiece() != ChessPiece::Piece::EMPTY && piece.getColor() != color){
            moves.emplace_back(x+rd, y+rd);
            break;
        }
        else break;
    }

    int ld=1;
    while(x+ld <= 7 && y-ld >= 0){
        ChessPiece piece = {board[x+ld][y-ld]->getPiece(), board[x+ld][y-ld]->getColor()};
        if(piece.getPiece() == ChessPiece::Piece::EMPTY){
            moves.emplace_back(x+ld, y-ld);
            ld++;
        }
        else if(piece.getPiece() != ChessPiece::Piece::EMPTY && piece.getColor() != color){
            moves.emplace_back(x+ld, y-ld);
            break;
        }
        else break;
    }
    return moves;
}

std::vector<std::pair<int, int>> ChessBoardState::find_knight_moves(int x, int y, ChessPiece::Color color) {
    std::vector<std::pair<int, int>> moves;

    if(x-2 >= 0){
        if(y-1 >= 0){
            if(board[x-2][y-1]->getPiece() == ChessPiece::Piece::EMPTY)
                moves.emplace_back(x-2, y-1);
            else if(board[x-2][y-1]->getPiece() != ChessPiece::Piece::EMPTY && board[x-2][y-1]->getColor() != color)
                moves.emplace_back(x-2, y-1);
        }
        if(y+1 <= 7){
            if(board[x-2][y+1]->getPiece() == ChessPiece::Piece::EMPTY)
                moves.emplace_back(x-2, y+1);
            else if(board[x-2][y+1]->getPiece() != ChessPiece::Piece::EMPTY && board[x-2][y+1]->getColor() != color)
                moves.emplace_back(x-2, y+1);
        }
    }

    if(x+2 <= 7){
        if(y-1 >= 0){
            if(board[x+2][y-1]->getPiece() == ChessPiece::Piece::EMPTY)
                moves.emplace_back(x+2, y-1);
            else if(board[x+2][y-1]->getPiece() != ChessPiece::Piece::EMPTY && board[x+2][y-1]->getColor() != color)
                moves.emplace_back(x+2, y-1);
        }
        if(y+1 <= 7){
            if(board[x+2][y+1]->getPiece() == ChessPiece::Piece::EMPTY)
                moves.emplace_back(x+2, y+1);
            else if(board[x+2][y+1]->getPiece() != ChessPiece::Piece::EMPTY && board[x+2][y+1]->getColor() != color)
                moves.emplace_back(x+2, y+1);
        }
    }

    if(y+2 <= 7){
        if(x-1 >= 0){
            if(board[x-1][y+2]->getPiece() == ChessPiece::Piece::EMPTY)
                moves.emplace_back(x-1, y+2);
            else if(board[x-1][y+2]->getPiece() != ChessPiece::Piece::EMPTY && board[x-1][y+2]->getColor() != color)
                moves.emplace_back(x-1, y+2);
        }
        if(x+1 <= 7){
            if(board[x+1][y+2]->getPiece() == ChessPiece::Piece::EMPTY)
                moves.emplace_back(x+1, y+2);
            else if(board[x+1][y+2]->getPiece() != ChessPiece::Piece::EMPTY && board[x+1][y+2]->getColor() != color)
                moves.emplace_back(x+1, y+2);
        }
    }

    if(y-2 >= 0){
        if(x-1 >= 0){
            if(board[x-1][y-2]->getPiece() == ChessPiece::Piece::EMPTY)
                moves.emplace_back(x-1, y-2);
            else if(board[x-1][y-2]->getPiece() != ChessPiece::Piece::EMPTY && board[x-1][y-2]->getColor() != color)
                moves.emplace_back(x-1, y-2);
        }
        if(x+1 <= 7){
            if(board[x+1][y-2]->getPiece() == ChessPiece::Piece::EMPTY)
                moves.emplace_back(x+1, y-2);
            else if(board[x+1][y-2]->getPiece() != ChessPiece::Piece::EMPTY && board[x+1][y-2]->getColor() != color)
                moves.emplace_back(x+1, y-2);
        }
    }
    return moves;
}

std::vector<std::pair<int, int>> ChessBoardState::find_pawn_moves(int x, int y, ChessPiece::Color color) {
    std::vector<std::pair<int, int>> moves;

    if(color == ChessPiece::Color::WHITE){
        if(x == 6){
            if(board[x-1][y]->getPiece() == ChessPiece::Piece::EMPTY && board[x-2][y]->getPiece() == ChessPiece::Piece::EMPTY) moves.emplace_back(x-2, y);
        }
        if(x-1 >= 0){
            if(board[x-1][y]->getPiece() == ChessPiece::Piece::EMPTY) moves.emplace_back(x-1, y);
            if(y-1 >= 0 && board[x-1][y-1]->getPiece() != ChessPiece::Piece::EMPTY && board[x-1][y-1]->getColor() != color)
                moves.emplace_back(x-1, y-1);
            if(y+1 <= 7 && board[x-1][y+1]->getPiece() != ChessPiece::Piece::EMPTY && board[x-1][y+1]->getColor() != color)
                moves.emplace_back(x-1, y+1);
        }
    }

    else if(color == ChessPiece::Color::BLACK){
        if(x == 1){
            if(board[x+1][y]->getPiece() == ChessPiece::Piece::EMPTY && board[x+2][y]->getPiece() == ChessPiece::Piece::EMPTY) moves.emplace_back(x+2, y);
        }
        if(x+1 <= 7){
            if(board[x+1][y]->getPiece() == ChessPiece::Piece::EMPTY) moves.emplace_back(x+1, y);
            if(y-1 >= 0 && board[x+1][y-1]->getPiece() != ChessPiece::Piece::EMPTY && board[x+1][y-1]->getColor() != color)
                moves.emplace_back(x+1, y-1);
            if(y+1 <= 7 && board[x+1][y+1]->getPiece() != ChessPiece::Piece::EMPTY && board[x+1][y+1]->getColor() != color)
                moves.emplace_back(x+1, y+1);
        }
    }
    return moves;
}

std::vector<std::pair<int, int>> ChessBoardState::find_rook_moves(int x, int y, ChessPiece::Color color) {
    std::vector<std::pair<int, int>> moves;

    for(int up=x-1; up>=0; up--){
        ChessPiece piece = {board[up][y]->getPiece(), board[up][y]->getColor()};
        if(piece.getPiece() == ChessPiece::Piece::EMPTY)
            moves.emplace_back(up, y);
        else if(piece.getPiece() != ChessPiece::Piece::EMPTY && piece.getColor() != color){
            moves.emplace_back(up, y);
            break;
        }
        else break;
    }

    for(int down=x+1; down<=7; down++){
        ChessPiece piece = {board[down][y]->getPiece(), board[down][y]->getColor()};
        if(piece.getPiece() == ChessPiece::Piece::EMPTY)
            moves.emplace_back(down, y);
        else if(piece.getPiece() != ChessPiece::Piece::EMPTY && piece.getColor() != color){
            moves.emplace_back(down, y);
            break;
        }
        else break;
    }

    for(int left=y-1; left >=0; left--){
        ChessPiece piece = {board[x][left]->getPiece(), board[x][left]->getColor()};
        if(piece.getPiece() == ChessPiece::Piece::EMPTY)
            moves.emplace_back(x, left);
        else if(piece.getPiece() != ChessPiece::Piece::EMPTY && piece.getColor() != color){
            moves.emplace_back(x, left);
            break;
        }
        else break;
    }

    for(int right=y+1; right<=7; right++){
        ChessPiece piece = {board[x][right]->getPiece(), board[x][right]->getColor()};
        if(piece.getPiece() == ChessPiece::Piece::EMPTY)
            moves.emplace_back(x, right);
        else if(piece.getPiece() != ChessPiece::Piece::EMPTY && piece.getColor() != color){
            moves.emplace_back(x, right);
            break;
        }
        else break;
    }
    return moves;
}

std::vector<std::pair<int, int>> ChessBoardState::find_queen_moves(int x, int y, ChessPiece::Color color) {
    std::vector<std::pair<int, int>> moves, element1, element2;
    element1 = find_rook_moves(x, y, color);
    element2 = find_bishop_moves(x, y, color);
    moves.insert(moves.end(), element1.begin(), element1.end());
    moves.insert(moves.end(), element2.begin(), element2.end());

    return moves;
}

std::vector<std::pair<int, int>> ChessBoardState::find_king_moves(int x, int y, ChessPiece::Color color) {
    std::vector<std::pair<int, int>> moves;

    if(x-1 >= 0){
        if(board[x-1][y]->getPiece() == ChessPiece::Piece::EMPTY)
            moves.emplace_back(x-1, y);
        if(board[x-1][y]->getPiece() != ChessPiece::Piece::EMPTY && board[x-1][y]->getColor() != color)
            moves.emplace_back(x-1, y);
    }

    if(x+1 <= 7){
        if(board[x+1][y]->getPiece() == ChessPiece::Piece::EMPTY)
            moves.emplace_back(x+1, y);
        if(board[x+1][y]->getPiece() != ChessPiece::Piece::EMPTY && board[x+1][y]->getColor() != color)
            moves.emplace_back(x+1, y);
    }

    if(y+1 <= 7){
        if(board[x][y+1]->getPiece() == ChessPiece::Piece::EMPTY)
            moves.emplace_back(x, y+1);
        if(board[x][y+1]->getPiece() != ChessPiece::Piece::EMPTY && board[x][y+1]->getColor() != color)
            moves.emplace_back(x, y+1);
    }

    if(y-1 >= 0){
        if(board[x][y-1]->getPiece() == ChessPiece::Piece::EMPTY)
            moves.emplace_back(x, y-1);
        if(board[x][y-1]->getPiece() != ChessPiece::Piece::EMPTY && board[x][y-1]->getColor() != color)
            moves.emplace_back(x, y-1);
    }

    if(x-1 >= 0 && y+1 <= 7){
        if(board[x-1][y+1]->getPiece() == ChessPiece::Piece::EMPTY)
            moves.emplace_back(x-1, y+1);
        if(board[x-1][y+1]->getPiece() != ChessPiece::Piece::EMPTY && board[x-1][y+1]->getColor() != color)
            moves.emplace_back(x-1, y+1);
    }

    if(x-1 >= 0 && y-1 >= 0){
        if(board[x-1][y-1]->getPiece() == ChessPiece::Piece::EMPTY)
            moves.emplace_back(x-1, y-1);
        if(board[x-1][y-1]->getPiece() != ChessPiece::Piece::EMPTY && board[x-1][y-1]->getColor() != color)
            moves.emplace_back(x-1, y-1);
    }

    if(x+1 <= 7 && y+1 <= 7){
        if(board[x+1][y+1]->getPiece() == ChessPiece::Piece::EMPTY)
            moves.emplace_back(x+1, y+1);
        if(board[x+1][y+1]->getPiece() != ChessPiece::Piece::EMPTY && board[x+1][y+1]->getColor() != color)
            moves.emplace_back(x+1, y+1);
    }

    if(x+1 <= 7 && y-1 >= 0){
        if(board[x+1][y-1]->getPiece() == ChessPiece::Piece::EMPTY)
            moves.emplace_back(x+1, y-1);
        if(board[x+1][y-1]->getPiece() != ChessPiece::Piece::EMPTY && board[x+1][y-1]->getColor() != color)
            moves.emplace_back(x+1, y-1);
    }
    return moves;
}