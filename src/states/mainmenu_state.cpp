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
    wrefresh(m_win);

    initMenu(game);
}

void MainMenuState::exit(SnakeGame* game) {
    wclear(m_win);
    clear();
}

void MainMenuState::execute(SnakeGame* game) {
    int choice;
    while (true) {
        m_menu.draw(m_win, 1, 1);

        choice = getch();
        if (m_menu.handleInput(choice)) {
            break;
        }
    }
}

void MainMenuState::initMenu(SnakeGame* game) {
    m_menu = Menu(3);
    m_menu.setOption(0, "Start", [game]() { game->setState(PlayState::getInstance()); });
    m_menu.setOption(1, "Settings", [game]() { printw("Settings option selected."); refresh();
        int choice = getch();
        game->setState(MainMenuState::getInstance());
    });
    m_menu.setOption(2, "Exit", [game]() { game->endGame(); });
}