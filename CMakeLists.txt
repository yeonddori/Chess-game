cmake_minimum_required(VERSION 3.24)
project(Chess_game)
set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(sfml
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.5.x)
FetchContent_MakeAvailable(sfml)

add_executable(Chess_game ChessBoardState.h ChessBoardState.cpp ChessPiece.cpp ChessPiece.h SFMLChessGame.h SFMLChessGame.cpp ChessGame.cpp)
target_link_libraries(Chess_game sfml-system sfml-window sfml-graphics sfml-audio)