#include "states/play_state.hpp"
#include "states/gameover_state.hpp"
#include <string>
#include <fstream>

PlayState& PlayState::getInstance() {
    static PlayState instance;
    return instance;
}

void PlayState::enter(SnakeGame* game) {
    nodelay(stdscr, TRUE);
    refresh();
    m_gameOver = false;
    m_pause = false;
    m_score = 0;
    m_generalWidth = game->getWidth();
    m_generalHeight = game->getHeight();
    m_win = game->getWindow();
    game->printBorder();
    refresh();
    wrefresh(m_win);

    int x, y;
    getbegyx(m_win, y, x);
    m_gameWin = newwin(m_height, m_width, y + 1, x + 2);
    box(m_gameWin, 0, 0);
    wrefresh(m_gameWin);
    wrefresh(m_win);
    refresh();
    drawInstruct();
    wrefresh(m_win);

    auto level = game->getCurrentLevel();
    if (level.empty()) {
        defaultLevel();
    }
    else {
        mvwprintw(m_gameWin, 0, 1, " %s ", level.substr(0, level.find_last_of('.')).c_str());
        readLevel(game->getLevelsPath() + level);
    }
}

void PlayState::exit(SnakeGame* game) {
    game->setScore(m_score);
    game->setHighScore(m_score);

    delwin(m_gameWin);
    wclear(m_win);
    clear();
    refresh();
    wrefresh(m_win);
}

void PlayState::execute(SnakeGame* game) {
    draw();
    napms(DELAY);
    int ch = getch();
    checkInputForQP(ch);
    if (m_gameOver) {
        game->setState(GameOverState::getInstance());
        return;
    }
    if (m_pause) {
        return;
    }
    checkInputForMove(ch);
    makeMove();
}

void PlayState::makeMove() {
    auto nextMove = m_snake.predictMove();
    checkForTeleport(nextMove);

    if (m_wall.isWall(nextMove)) {
        m_gameOver = true;
        return;
    }
    if (m_food.isFood(nextMove)) {
        m_snake.moveToAndGrow(nextMove);
        m_food.getEaten();
        makeFood();
        m_score++;
        return;
    }

    if (m_snake.moveTo(nextMove) == MoveResult::IMPOSSIBLE) {
        m_gameOver = true;
    }
}

void PlayState::checkForTeleport(coords_t &nextMove) const {
    if (nextMove.first < 1 || nextMove.first >= m_width - 1) {
        nextMove.first = abs(nextMove.first - m_width + 2);
    }

    if (nextMove.second < 1 || nextMove.second >= m_height - 1) {
        nextMove.second = abs(nextMove.second - m_height + 2);
    }
}

void PlayState::checkInputForMove(int ch) {
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
        default:
            break;
    }
}

void PlayState::checkInputForQP(int ch) {
    if (ch == ERR) {
        return;
    }

    switch (ch) {
        case 'p':
            m_pause = !m_pause;
            break;
        case 'q':
            m_gameOver = true;
            break;
        default:
            break;
    }
}

void PlayState::draw() const {
    m_snake.draw(m_gameWin);
    m_food.draw(m_gameWin);
    m_wall.draw(m_gameWin);
    drawScore();
    wrefresh(m_gameWin);
    wrefresh(m_win);
    refresh();
    m_snake.erase(m_gameWin);
}

void PlayState::drawScore() const {
    mvwprintw(m_win, m_height + 1, 2, "Score: %d", m_score);
    auto lengthStr = "Length: " + std::to_string(m_snake.getLength());
    mvwprintw(m_win, m_height + 1, m_width + 2 - static_cast<int>(lengthStr.length()), "%s", lengthStr.c_str());
}

void PlayState::drawInstruct() const {
    mvwprintw(m_win, 2, m_width + 2, "Press 'p' to pause");
    mvwprintw(m_win, 3, m_width + 2, "Press 'q' to quit");
}

void PlayState::readLevel(const std::string& levelPath) {
    if (levelPath.empty()) {
        defaultLevel();
        return;
    }

    m_wall = Wall();

    std::ifstream levelFile(levelPath);
    std::string line;
    int y = 1;
    while (std::getline(levelFile, line)) {
//        if (line.empty()) {
//            ++y;
//            continue;
//        }
        for (int x = 0; x < static_cast<int>(line.length()); ++x) {
            if (line[x] == '#') {
                m_wall.addWall(coords_t{x + 1, y});
            }
            if (line[x] == '0') {
                m_snake = Snake(x + 1, y);
            }
        }
        ++y;
    }
    m_food = Food(m_width, m_height);
    makeFood();
}

void PlayState::defaultLevel() {
    m_snake = Snake(m_width / 2, m_height / 2);
    m_wall = Wall();
    for (int i = 1; i < m_width - 1; i++) {
        m_wall.addWall(coords_t{i, 1});
        m_wall.addWall(coords_t{i, m_height - 2});
    }
    m_food = Food(m_width, m_height);
    makeFood();
}

void PlayState::makeFood() {
    while (m_snake.isSnake(m_food.getCoords()) || m_wall.isWall(m_food.getCoords())) {
        m_food.createNew(m_width, m_height);
    }
}