#include "states/mainmenu_state.hpp"
#include "states/play_state.hpp"

MainMenuState& MainMenuState::getInstance() {
    static MainMenuState instance;
    return instance;
}

void MainMenuState::enter(SnakeGame* game) {
    nodelay(stdscr, FALSE);
    m_win = game->getWindow();
    box(m_win, 0, 0);
    refresh();
    mvwprintw(m_win, 1, 1, "Snake Game");
    mvwprintw(m_win, 2, 1, "Press 's' key to start");
    mvwprintw(m_win, 3, 1, "Press 'q' key to exit");
    wrefresh(m_win);
}

void MainMenuState::exit(SnakeGame* game) {
    wclear(m_win);
    clear();
}

void MainMenuState::execute(SnakeGame* game) {
    while (true) {
        int ch = getch();
        if (ch == 's') {
            game->setState(PlayState::getInstance());
            break;
        }
        if (ch == 'q') {
            game->endGame();
            break;
        }
    }
}