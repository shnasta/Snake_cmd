#include "states/play_state.hpp"
#include "states/gameover_state.hpp"
#include <string>

PlayState& PlayState::getInstance() {
    static PlayState instance;
    return instance;
}

void PlayState::enter(SnakeGame* game) {
    nodelay(stdscr, TRUE);
    refresh();
    m_width = game->getWidth();
    m_height = game->getHeight();
    m_gameOver = false;
    m_score = 0;
    m_snake = Snake(m_width / 2, m_height / 2);
    m_food = Food(m_width, m_height);
    m_wall = Wall();
    for (int i = 1; i < m_width - 1; i++) {
        m_wall.addWall(coords_t{i, 1});
        m_wall.addWall(coords_t{i, m_height - 2});
    }

    m_win = game->getWindow();
    box(m_win, 0, 0);
    refresh();
    wrefresh(m_win);
}

void PlayState::exit(SnakeGame* game) {
    game->setScore(m_score);
    game->setHighScore(m_score);

    wclear(m_win);
    clear();
}

void PlayState::execute(SnakeGame* game) {
    while (true) {
        makeMove();
        draw();
        napms(DELAY);
        if (m_gameOver) {
            game->setState(GameOverState::getInstance());
            break;
        }
    }
}

void PlayState::makeMove() {
    checkInput();
    auto nextMove = m_snake.predictMove();
    checkForTeleport(nextMove);


    if (m_wall.isWall(nextMove)) {
        m_gameOver = true;
        return;
    }
    if (m_food.isFood(nextMove)) {
        m_snake.moveToAndGrow(nextMove);
        m_food.getEaten();
        while (m_snake.isSnake(m_food.getCoords()) || m_wall.isWall(m_food.getCoords())) {
            m_food.createNew(m_width, m_height);
        }
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

void PlayState::checkInput() {
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
            m_gameOver = true;
            break;
        default:
            break;
    }
}

void PlayState::draw() const {
    m_snake.draw(m_win);
    m_food.draw(m_win);
    m_wall.draw(m_win);
    drawScore();
    wrefresh(m_win);
    m_snake.erase(m_win);
}

void PlayState::drawScore() const {
    mvprintw(m_height, 0, "Score: %d", m_score);
    auto lengthStr = "Length: " + std::to_string(m_snake.getLength());
    mvprintw(m_height, m_width - static_cast<int>(lengthStr.length()), "%s", lengthStr.c_str());
}
