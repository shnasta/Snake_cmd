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
    mvwprintw(m_win, 2, 1, "Press 'q' key to exit");
    mvwprintw(m_win, 3, 1, "Press 'r' key to restart");
    mvwprintw(m_win, 4, 1, "Score: %d", m_score);
    mvwprintw(m_win, 5, 1, "High Score: %d", m_highScore);
    wrefresh(m_win);
}

void GameOverState::exit(SnakeGame* game) {
    wclear(m_win);
    clear();
}

void GameOverState::execute(SnakeGame* game) {
    while (true) {
        int ch = getch();
        if (ch == 'q') {
            game->endGame();
            break;
        }
        if (ch == 'r') {
            game->setState(PlayState::getInstance());
            break;
        }
    }
}