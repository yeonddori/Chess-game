cmake_minimum_required(VERSION 3.22)
project(Chess_game)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
set(SFML_VERSION 2.5.1)

FetchContent_Declare(
        SFML
        URL "https://github.com/SFML/SFML/archive/${SFML_VERSION}.zip"
)

FetchContent_MakeAvailable(sfml)

add_executable(sfml_hello2 main.cpp)

# Set include directory search paths
target_include_directories(sfml_hello2
        PRIVATE
        "${PROJECT_BINARY_DIR}"
        )

# Link executable to required SFML libraries
target_link_libraries(sfml_hello2 sfml-graphics)

# Install target
install(TARGETS sfml_hello2 DESTINATION bin)


