#include "snake_game.hpp"
#include "states/mainmenu_state.hpp"

SnakeGame::SnakeGame() {
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(0);
    m_win = newwin(MIN_HEIGHT, MIN_WIDTH, 0, 0);
    m_width = MIN_WIDTH;
    m_height = MIN_HEIGHT;
    refresh();
    wrefresh(m_win);
}

SnakeGame::~SnakeGame() {
    endGame();
}

void SnakeGame::run() {
    setState(MainMenuState::getInstance());
}

void SnakeGame::setState(BasicState<SnakeGame> &state) {
    if (m_currentState)
        m_currentState->exit(this);
    m_currentState = &state;
    m_currentState->enter(this);

    m_currentState->execute(this);
}

void SnakeGame::endGame() {
    if (m_currentState)
        m_currentState->exit(this);
    endwin();
}