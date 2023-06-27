#include "states/gameover_state.hpp"
#include "states/play_state.hpp"

GameOverState& GameOverState::getInstance() {
    static GameOverState instance;
    return instance;
}

void GameOverState::enter(SnakeGame* game) {
    nodelay(stdscr, FALSE);
    m_score = game->getScore();
    m_highScore = game->getHighScore();
    m_win = game->getWindow();
    box(m_win, 0, 0);
    refresh();
    mvwprintw(m_win, 1, 1, "Game Over!");
    mvwprintw(m_win, 2, 1, "Score:      %d", m_score);
    mvwprintw(m_win, 3, 1, "High Score: %d", m_highScore);
    wrefresh(m_win);

    initMenu(game);
}

void GameOverState::exit(SnakeGame* game) {
    wclear(m_win);
    clear();
}

void GameOverState::execute(SnakeGame* game) {
    while (true) {
        m_menu.draw(m_win, 5, 1);

        int choice = getch();
        if (m_menu.handleInput(choice)) {
            break;
        }
    }
}

void GameOverState::initMenu(SnakeGame* game) {
    m_menu = Menu(2);
    m_menu.setOption(0, "Restart", [game]() { game->setState(PlayState::getInstance()); });
    m_menu.setOption(1, "Quit", [game]() { game->endGame(); });
}