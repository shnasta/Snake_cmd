#include <stdexcept>
#include "snake_game.hpp"

SnakeGame::SnakeGame() : m_width(50), m_height(20),
                         m_snake(m_width / 2, m_height / 2),
                         m_food(m_width, m_height) {
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(0);
//    getmaxyx(stdscr, m_height, m_width);
    m_win = newwin(m_height, m_width, 0, 0);
    box(m_win, 0, 0);
    refresh();
    wrefresh(m_win);
}

void SnakeGame::run() {
    m_state = GameState::PLAYING;
    while (m_state != GameState::GAME_OVER) {
        makeMove();
        draw();
        napms(DELAY);
    }
    endwin();
}

void SnakeGame::makeMove() {
    checkInput();
    if (m_food.isFood(m_snake.predictMove())) {
        m_snake.moveAndGrow();
        m_food.getEaten();
        while (m_snake.isSnake(m_food.getCoords())) {
            m_food.createNew(m_width, m_height);
        }
        m_score++;
        return;
    }

    try {
        m_snake.move();
    } catch (std::runtime_error &e) {
        m_state = GameState::GAME_OVER;
    }
}

void SnakeGame::checkInput() {
    int ch = getch();
    if (ch == ERR) {
        return;
    }
    switch (ch) {
        case KEY_UP:
        case 'w':
            m_snake.setDirection(UP);
            break;
        case KEY_DOWN:
        case 's':
            m_snake.setDirection(DOWN);
            break;
        case KEY_LEFT:
        case 'a':
            m_snake.setDirection(LEFT);
            break;
        case KEY_RIGHT:
        case 'd':
            m_snake.setDirection(RIGHT);
            break;
        case 'q':
            m_state = GameState::GAME_OVER;
            break;
        default:
            break;
    }
}

void SnakeGame::draw() const {
    m_snake.draw(m_win);
    m_food.draw(m_win);
    drawScore();
    wrefresh(m_win);
    m_snake.erase(m_win);
}

void SnakeGame::drawScore() const {
    mvprintw(m_height, 0, "Score: %d", m_score);
    auto length_str = "Length: " + std::to_string(m_snake.getLength());
    mvprintw(m_height, m_width - static_cast<int>(length_str.length()), "%s", length_str.c_str());
}