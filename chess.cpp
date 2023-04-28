#include "chess.h"
#include <iostream>

void print_board(ChessBoard const board){
    std::cout << "  0  1  2  3  4  5  6  7" << std::endl;
    for(int i=0; i<BOARD_SIZE; i++){
        std::cout << i << " ";
        for(int j=0; j<BOARD_SIZE; j++){
            ChessPiece piece = board[i][j];
            switch(piece.piece){
                case EMPTY:  std::cout << "   "; break;
                case PAWN:   std::cout << (piece.color == WHITE ? "Pw " : "Pb "); break;
                case ROOK:   std::cout << (piece.color == WHITE ? "Rw " : "Rb "); break;
                case KNIGHT: std::cout << (piece.color == WHITE ? "Nw " : "Nb "); break;
                case BISHOP: std::cout << (piece.color == WHITE ? "Bw " : "Bb "); break;
                case QUEEN:  std::cout << (piece.color == WHITE ? "Qw " : "Qb "); break;
                case KING:   std::cout << (piece.color == WHITE ? "Kw " : "Kb "); break;
            }
        }
        std::cout << std::endl;
    }
}

std::vector<std::pair<int, int>> find_bishop_moves(ChessBoard board, int x, int y, Color color){
    std::vector<std::pair<int, int>> moves;

    int ru=1;
    while(x-ru >= 0 && y+ru <= 7){
        ChessPiece piece = board[x-ru][y+ru];
        if(piece.piece == EMPTY){
            moves.emplace_back(x-ru, y+ru);
            ru++;
            }
        else if(piece.piece != EMPTY && piece.color != color){
            moves.emplace_back(x-ru, y+ru);
            break;
        }
        else break;
    }

    int lu=1;
    while(x-lu >= 0 && y-lu >= 0){
        ChessPiece piece = board[x-lu][y-lu];
        if(piece.piece == EMPTY){
            moves.emplace_back(x-lu, y-lu);
            lu++;
        }
        else if(piece.piece != EMPTY && piece.color != color){
            moves.emplace_back(x-lu, y-lu);
            break;
        }
        else break;
    }

    int rd=1;
    while(x+rd <= 7 && y+rd <= 7){
        ChessPiece piece = board[x+rd][y+rd];
        if(piece.piece == EMPTY){
            moves.emplace_back(x+rd, y+rd);
            rd++;
        }
        else if(piece.piece != EMPTY && piece.color != color){
            moves.emplace_back(x+rd, y+rd);
            break;
        }
        else break;
    }

    int ld=1;
    while(x+ld <= 7 && y-ld >= 0){
        ChessPiece piece = board[x+ld][y-ld];
        if(piece.piece == EMPTY){
            moves.emplace_back(x+ld, y-ld);
            ld++;
        }
        else if(piece.piece != EMPTY && piece.color != color){
            moves.emplace_back(x+ld, y-ld);
            break;
        }
        else break;
    }
    return moves;
}

std::vector<std::pair<int, int>> find_knight_moves(ChessBoard board, int x, int y, Color color){
    std::vector<std::pair<int, int>> moves;

    if(x-2 >= 0){
        if(y-1 >= 0){
            if(board[x-2][y-1].piece == EMPTY)
                moves.emplace_back(x-2, y-1);
            else if(board[x-2][y-1].piece != EMPTY && board[x-2][y-1].color != color)
                moves.emplace_back(x-2, y-1);
        }
        if(y+1 <= 7){
            if(board[x-2][y+1].piece == EMPTY)
                moves.emplace_back(x-2, y+1);
            else if(board[x-2][y+1].piece != EMPTY && board[x-2][y+1].color != color)
                moves.emplace_back(x-2, y+1);
        }
    }

    if(x+2 <= 7){
        if(y-1 >= 0){
            if(board[x+2][y-1].piece == EMPTY)
                moves.emplace_back(x+2, y-1);
            else if(board[x+2][y-1].piece != EMPTY && board[x+2][y-1].color != color)
                moves.emplace_back(x+2, y-1);
        }
        if(y+1 <= 7){
            if(board[x+2][y+1].piece == EMPTY)
                moves.emplace_back(x+2, y+1);
            else if(board[x+2][y+1].piece != EMPTY && board[x+2][y+1].color != color)
                moves.emplace_back(x+2, y+1);
        }
    }

    if(y+2 <= 7){
        if(x-1 >= 0){
            if(board[x-1][y+2].piece == EMPTY)
                moves.emplace_back(x-1, y+2);
            else if(board[x-1][y+2].piece != EMPTY && board[x-1][y+2].color != color)
                moves.emplace_back(x-1, y+2);
        }
        if(x+1 <= 7){
            if(board[x+1][y+2].piece == EMPTY)
                moves.emplace_back(x+1, y+2);
            else if(board[x+1][y+2].piece != EMPTY && board[x+1][y+2].color != color)
                moves.emplace_back(x+1, y+2);
        }
    }

    if(y-2 >= 0){
        if(x-1 >= 0){
            if(board[x-1][y-2].piece == EMPTY)
                moves.emplace_back(x-1, y-2);
            else if(board[x-1][y-2].piece != EMPTY && board[x-1][y-2].color != color)
                moves.emplace_back(x-1, y-2);
        }
        if(x+1 <= 7){
            if(board[x+1][y-2].piece == EMPTY)
                moves.emplace_back(x+1, y-2);
            else if(board[x+1][y-2].piece != EMPTY && board[x+1][y-2].color != color)
                moves.emplace_back(x+1, y-2);
        }
    }
    return moves;
}

std::vector<std::pair<int, int>> find_pawn_moves(ChessBoard board,int x, int y, Color color){
    std::vector<std::pair<int, int>> moves;

    if(color == WHITE){
        if(x == 6){
            if(board[x-1][y].piece == EMPTY && board[x-2][y].piece == EMPTY) moves.emplace_back(x-2, y);
        }
        if(x-1 >= 0){
            if(board[x-1][y].piece == EMPTY) moves.emplace_back(x-1, y);
            if(y-1 >= 0 && board[x-1][y-1].piece != EMPTY && board[x-1][y-1].color != color)
                moves.emplace_back(x-1, y-1);
            if(y+1 <= 7 && board[x-1][y+1].piece != EMPTY && board[x-1][y+1].color != color)
                moves.emplace_back(x-1, y+1);
        }
    }

    else if(color == BLACK){
        if(x == 1){
            if(board[x+1][y].piece == EMPTY && board[x+2][y].piece == EMPTY) moves.emplace_back(x+2, y);
        }
        if(x+1 <= 7){
            if(board[x+1][y].piece == EMPTY) moves.emplace_back(x+1, y);
            if(y-1 >= 0 && board[x+1][y-1].piece != EMPTY && board[x+1][y-1].color != color)
                moves.emplace_back(x+1, y-1);
            if(y+1 <= 7 && board[x+1][y+1].piece != EMPTY && board[x+1][y+1].color != color)
                moves.emplace_back(x+1, y+1);
        }
    }
    return moves;
}

std::vector<std::pair<int, int>> find_rook_moves(ChessBoard board,int x, int y, Color color){
    std::vector<std::pair<int, int>> moves;

    for(int up=x-1; up>=0; up--){
        ChessPiece piece = board[up][y];
        if(piece.piece == EMPTY)
            moves.emplace_back(up, y);
        else if(piece.piece != EMPTY && piece.color != color){
            moves.emplace_back(up, y);
            break;
        }
        else break;
    }

    for(int down=x+1; down<=7; down++){
        ChessPiece piece = board[down][y];
        if(piece.piece == EMPTY)
            moves.emplace_back(down, y);
        else if(piece.piece != EMPTY && piece.color != color){
            moves.emplace_back(down, y);
            break;
        }
        else break;
    }

    for(int left=y-1; left >=0; left--){
        ChessPiece piece = board[x][left];
        if(piece.piece == EMPTY)
            moves.emplace_back(x, left);
        else if(piece.piece != EMPTY && piece.color != color){
            moves.emplace_back(x, left);
            break;
        }
        else break;
    }

    for(int right=y+1; right<=7; right++){
        ChessPiece piece = board[x][right];
        if(piece.piece == EMPTY)
            moves.emplace_back(x, right);
        else if(piece.piece != EMPTY && piece.color != color){
            moves.emplace_back(x, right);
            break;
        }
        else break;
    }
    return moves;
}

std::vector<std::pair<int, int>> find_queen_moves(ChessBoard board,int x, int y, Color color){
    std::vector<std::pair<int, int>> moves, element1, element2;
    element1 = find_rook_moves(board, x, y, color);
    element2 = find_bishop_moves(board, x, y, color);
    moves.insert(moves.end(), element1.begin(), element1.end());
    moves.insert(moves.end(), element2.begin(), element2.end());

    return moves;
}
std::vector<std::pair<int, int>> find_king_moves(ChessBoard board,int x, int y, Color color){
    std::vector<std::pair<int, int>> moves;

    if(x-1 >= 0){
        if(board[x-1][y].piece == EMPTY)
            moves.emplace_back(x-1, y);
        if(board[x-1][y].piece != EMPTY && board[x-1][y].color != color)
            moves.emplace_back(x-1, y);
    }

    if(x+1 <= 7){
        if(board[x+1][y].piece == EMPTY)
            moves.emplace_back(x+1, y);
        if(board[x+1][y].piece != EMPTY && board[x+1][y].color != color)
            moves.emplace_back(x+1, y);
    }

    if(y+1 <= 7){
        if(board[x][y+1].piece == EMPTY)
            moves.emplace_back(x, y+1);
        if(board[x][y+1].piece != EMPTY && board[x][y+1].color != color)
            moves.emplace_back(x, y+1);
    }

    if(y-1 >= 0){
        if(board[x][y-1].piece == EMPTY)
            moves.emplace_back(x, y-1);
        if(board[x][y-1].piece != EMPTY && board[x][y-1].color != color)
            moves.emplace_back(x, y-1);
    }

    if(x-1 >= 0 && y+1 <= 7){
        if(board[x-1][y+1].piece == EMPTY)
            moves.emplace_back(x-1, y+1);
        if(board[x-1][y+1].piece != EMPTY && board[x-1][y+1].color != color)
            moves.emplace_back(x-1, y+1);
    }

    if(x-1 >= 0 && y-1 >= 0){
        if(board[x-1][y-1].piece == EMPTY)
            moves.emplace_back(x-1, y-1);
        if(board[x-1][y-1].piece != EMPTY && board[x-1][y-1].color != color)
            moves.emplace_back(x-1, y-1);
    }

    if(x+1 <= 7 && y+1 <= 7){
        if(board[x+1][y+1].piece == EMPTY)
            moves.emplace_back(x+1, y+1);
        if(board[x+1][y+1].piece != EMPTY && board[x+1][y+1].color != color)
            moves.emplace_back(x+1, y+1);
    }

    if(x+1 <= 7 && y-1 >= 0){
        if(board[x+1][y-1].piece == EMPTY)
            moves.emplace_back(x+1, y-1);
        if(board[x+1][y-1].piece != EMPTY && board[x+1][y-1].color != color)
            moves.emplace_back(x+1, y-1);
    }
    return moves;
}