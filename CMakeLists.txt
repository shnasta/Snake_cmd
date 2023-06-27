cmake_minimum_required(VERSION 3.17)

set(PROJECT_NAME snake_game)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE HEADERS "inc/*.hpp")
file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE inc)
target_include_directories(${PROJECT_NAME} PRIVATE src)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
target_link_libraries(snake_game ${CURSES_LIBRARIES})