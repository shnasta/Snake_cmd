#ifndef SNAKE_GAME_SNAKE_GAME_HPP
#define SNAKE_GAME_SNAKE_GAME_HPP

#include <ncurses.h>
#include "states/basic_state.hpp"

class SnakeGame {
public:
    SnakeGame();

    ~SnakeGame();

    void run();

    void setState(BasicState<SnakeGame> &state);

    void endGame();

    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }
    WINDOW* getWindow() const { return m_win; }
    int getScore() const { return m_score; }
    void setScore(int score) { m_score = score; }
    int getHighScore() const { return m_highScore; }
    void setHighScore(int highScore) { if (highScore > m_highScore) m_highScore = highScore; }
private:
    BasicState<SnakeGame> *m_currentState = nullptr;

    int MIN_WIDTH = 30;
    int MIN_HEIGHT = 15;
    int m_width = 0;
    int m_height = 0;
    WINDOW *m_win = nullptr;

    int m_score = 0;
    int m_highScore = 0;
};

#endif //SNAKE_GAME_SNAKE_GAME_HPP
