cmake_minimum_required(VERSION 3.24)
project(Chess_game)

set(CMAKE_CXX_STANDARD 17)

add_executable(Chess_game ChessGame.cpp ChessBoardState.h ChessBoardState.cpp chess.h chess.cpp)

set(SFML_STATIC_LIBRARIES TRUE)
# 경로 맞추기
set(SFML_DIR "C:/Program Files/SFML-2.5.1/lib/cmake/SFML")
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

# 경로 맞추기
include_directories("C:/Program Files/SFML-2.5.1/include")
target_link_libraries(Chess_game sfml-system sfml-window sfml-graphics sfml-audio)