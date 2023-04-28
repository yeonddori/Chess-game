#include "chess.h"
#include <iostream>
#include <algorithm>

bool make_move(ChessBoard &board, int from_x, int from_y) {
    ChessPiece piece = board[from_x][from_y];
    std::vector <std::pair<int, int>> legal_moves;

    switch (piece.piece) {
        case EMPTY:  return false;
        case PAWN:   legal_moves = find_pawn_moves(board, from_x, from_y, piece.color); break;
        case ROOK:   legal_moves = find_rook_moves(board, from_x, from_y, piece.color); break;
        case KNIGHT: legal_moves = find_knight_moves(board, from_x, from_y, piece.color); break;
        case BISHOP: legal_moves = find_bishop_moves(board, from_x, from_y, piece.color); break;
        case QUEEN:  legal_moves = find_queen_moves(board, from_x, from_y, piece.color); break;
        case KING:   legal_moves = find_king_moves(board, from_x, from_y, piece.color); break;
    }

    if(legal_moves.empty()) return false;
    else{
        std::sort(legal_moves.begin(), legal_moves.end());
        std::cout << "legal moves: ";
        int count = 0;
        for(const auto &i: legal_moves){
            std::cout << "(" << i.first << ", " << i.second << ") ";
            count++;
        }
        std::cout << std::endl;
        if(count == 0) std::cout << "Select a move (0): ";
        else std::cout << "Select a move (0-" << count-1 << "): ";

        int select; std::cin >> select;
        board[legal_moves[select].first][legal_moves[select].second] = piece;
        board[from_x][from_y] = ChessPiece();
        return true;
    }
}

int main() {
    ChessBoard board = {
            {{ROOK,   WHITE}, {KNIGHT, WHITE}, {BISHOP, WHITE}, {QUEEN, WHITE},{KING,  WHITE}, {BISHOP, WHITE}, {KNIGHT, WHITE}, {ROOK,   WHITE}},
            {{PAWN,   WHITE}, {PAWN,   WHITE}, {PAWN,   WHITE}, {PAWN,  WHITE}, {PAWN,  WHITE}, {PAWN,   WHITE}, {PAWN,   WHITE}, {PAWN,   WHITE}},
            {{EMPTY,  BLANK}, {EMPTY,  BLANK}, {EMPTY,  BLANK}, {EMPTY, BLANK}, {EMPTY, BLANK}, {EMPTY,  BLANK}, {EMPTY,  BLANK}, {EMPTY,  BLANK}},
            {{EMPTY,  BLANK}, {EMPTY,  BLANK}, {EMPTY,  BLANK}, {EMPTY, BLANK}, {EMPTY, BLANK}, {EMPTY,  BLANK}, {EMPTY,  BLANK}, {EMPTY,  BLANK}},
            {{EMPTY,  BLANK}, {EMPTY,  BLANK}, {EMPTY,  BLANK}, {EMPTY, BLANK}, {EMPTY, BLANK}, {EMPTY,  BLANK}, {EMPTY,  BLANK}, {EMPTY,  BLANK}},
            {{EMPTY,  BLANK}, {EMPTY,  BLANK}, {EMPTY,  BLANK}, {EMPTY, BLANK}, {EMPTY, BLANK}, {EMPTY,  BLANK}, {EMPTY,  BLANK}, {EMPTY,  BLANK}},
            {{PAWN,   BLACK}, {PAWN,   BLACK}, {PAWN,   BLACK}, {PAWN,  BLACK}, {PAWN,  BLACK}, {PAWN,   BLACK}, {PAWN,   BLACK}, {PAWN,   BLACK}},
            {{ROOK,   BLACK}, {KNIGHT, BLACK}, {BISHOP, BLACK}, {QUEEN, BLACK}, {KING,  BLACK}, {BISHOP, BLACK}, {KNIGHT, BLACK}, {ROOK,   BLACK}}
    };

    print_board(board);

    while (true) {
        int from_x, from_y;
        std::cout << "Select your piece (x y): ";
        std::cin >> from_x >> from_y;
        std::cin.ignore();
        if (from_x == -1 && from_y == -1) break;

        if (!make_move(board, from_x, from_y)) {
            std::cout << "Illegal move!\n";
            continue;
        }

        print_board(board);
    }

    return 0;
}