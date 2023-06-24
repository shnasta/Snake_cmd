#include <iostream>
#include <ncurses.h>
#include <unistd.h>
#include <vector>
#include "snake.hpp"
#include "snake_game.hpp"

int main() {
    SnakeGame game;
    game.run();
    return 0;
}

