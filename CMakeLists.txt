cmake_minimum_required(VERSION 3.20)
project(Snake_game)

set(CMAKE_CXX_STANDARD 23)

add_executable(Snake_game main.cpp GUI.cpp GUI.h Snake.cpp Snake.h)
set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/cpp/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(C:/cpp/SFML/include)
target_link_libraries(Snake_game sfml-system sfml-graphics sfml-audio)