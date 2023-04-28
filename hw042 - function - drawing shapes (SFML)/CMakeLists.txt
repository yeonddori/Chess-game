cmake_minimum_required(VERSION 3.24)
project(class)

set(CMAKE_CXX_STANDARD 17)

add_executable(class shape_main.cpp shape.h shape.cpp)

#include(FetchContent)
#set(SFML_VERSION 2.5.1)
#
#FetchContent_Declare(
#        SFML
#        URL "https://github.com/SFML/SFML/archive/${SFML_VERSION}.zip"
#)
#
#FetchContent_MakeAvailable(sfml)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR "C:/Program Files/SFML-2.5.1/lib/cmake/SFML")
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories("C:/Program Files/SFML-2.5.1/include")
target_link_libraries(class sfml-system sfml-window sfml-graphics sfml-audio)


