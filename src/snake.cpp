#include <algorithm>
#include <stdexcept>
#include <ncurses.h>
#include <iostream>
#include "snake.hpp"

Snake::Snake(int startX, int startY) {
    m_head = std::make_pair(startX, startY);
    m_body.resize(m_length);
    for (int i = m_length - 1; i >= 0; --i) {
        m_body[i] = std::make_pair(startX, startY + i);
    }
}

void Snake::setDirection(Direction direction) {
    if (direction == UP && m_direction == DOWN) {
        return;
    }
    if (direction == DOWN && m_direction == UP) {
        return;
    }
    if (direction == LEFT && m_direction == RIGHT) {
        return;
    }
    if (direction == RIGHT && m_direction == LEFT) {
        return;
    }

    m_direction = direction;
}

bool Snake::isSnake(coords_t coords) const {
    return std::find(m_body.begin(), m_body.end(), coords) != m_body.end();
}

Snake::coords_t Snake::predictMove() {
    switch (m_direction) {
        case UP:
            return std::make_pair(getX(), getY() - 1);
        case DOWN:
            return std::make_pair(getX(), getY() + 1);
        case LEFT:
            return std::make_pair(getX() - 1, getY());
        case RIGHT:
            return std::make_pair(getX() + 1, getY());
        default:
            throw std::runtime_error("Invalid direction!");
    }
}

void Snake::move() {
    coords_t newHead = predictMove();
    if (isSnake(newHead)) {
        throw std::runtime_error("Snake collided with itself!");
    }
    m_head = newHead;
    m_body.pop_back();
    m_body.emplace(m_body.begin(), newHead);
}

void Snake::moveAndGrow() {
    coords_t newHead = predictMove();
    m_head = newHead;
    m_length++;
    m_body.emplace(m_body.begin(), newHead);
}

void Snake::draw() const {
    for (const auto &coords : m_body) {
        mvprintw(coords.second, coords.first, "o");
    }
    mvprintw(getY(), getX(), "O");
}

void Snake::draw(WINDOW *win) const {
    for (const auto &coords : m_body) {
        mvwprintw(win, coords.second, coords.first, "o");
    }
    mvwprintw(win, getY(), getX(), "O");
}

void Snake::erase() const {
    for (const auto &coords : m_body) {
        mvprintw(coords.second, coords.first, " ");
    }
    mvprintw(getY(), getX(), " ");
}

void Snake::erase(WINDOW *win) const {
    for (const auto &coords : m_body) {
        mvwprintw(win, coords.second, coords.first, " ");
    }
    mvwprintw(win, getY(), getX(), " ");
}

void Snake::debugPrint() const {
    std::cout << "Head: (" << getX() << ", " << getY() << ")" << std::endl;
    std::cout << "Length: " << getLength() << std::endl;
    std::cout << "Body: ";
    for (const auto &coords : m_body) {
        std::cout << "(" << coords.first << ", " << coords.second << ") ";
    }
    std::cout << std::endl;
}