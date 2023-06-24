#ifndef SNAKE_GAME_SNAKE_GAME_HPP
#define SNAKE_GAME_SNAKE_GAME_HPP

#include <ncurses.h>
#include <unistd.h>
#include <vector>
#include "snake.hpp"
#include "food.hpp"

enum class GameState {
    NOT_STARTED,
    PLAYING,
    GAME_OVER
};

class SnakeGame {
public:
    SnakeGame();
    void run();

    void makeMove();
    void draw() const;
private:
    int DELAY = 300;
    WINDOW *m_win;
    int m_width;
    int m_height;

    Snake m_snake;
    Food m_food;

    GameState m_state = GameState::NOT_STARTED;
    int m_score = 0;

    void checkInput();

    void drawScore() const;
};
#endif //SNAKE_GAME_SNAKE_GAME_HPP
