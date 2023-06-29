#include "snake_game.hpp"
#include "states/mainmenu_state.hpp"

SnakeGame::SnakeGame() {
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(0);
    m_win = newwin(m_height, m_width, 0, 0);
//    m_width = MIN_WIDTH;
//    m_height = MIN_HEIGHT;
    refresh();
    wrefresh(m_win);
}

SnakeGame::~SnakeGame() {
    endGame();
}

void SnakeGame::run() {
    setState(MainMenuState::getInstance());
    while (!m_exit) {
        m_currentState->execute(this);
    }
    endGame();
}

void SnakeGame::setState(BasicState<SnakeGame> &state) {
    if (m_currentState)
        m_currentState->exit(this);
    m_currentState = &state;
    m_currentState->enter(this);
}

void SnakeGame::endGame() {
    if (m_currentState)
        m_currentState->exit(this);
    endwin();
}

void SnakeGame::printBorder() {
    if (m_viewSettings.border) {
        box(m_win, 0, 0);
    }
}

void SnakeGame::toggleBorder() {
    if (m_viewSettings.border) {
        wborder(m_win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    } else {
        box(m_win, 0, 0);
    }
    m_viewSettings.border = !m_viewSettings.border;
}

void SnakeGame::toggleCentered() {
    if (m_viewSettings.centered) {
        mvwin(m_win, 0, 0);
    } else {
        int width, height;
        getmaxyx(stdscr, height, width);
        mvwin(m_win, (height - m_height) / 2, (width - m_width) / 2);
    }
    m_viewSettings.centered = !m_viewSettings.centered;
}