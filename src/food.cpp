#include "food.hpp"
#include <random>
#include <ctime>

Food::Food(int width, int height) : m_width(width), m_height(height) {
    createNew(m_width, m_height);
}

void Food::createNew(int width, int height) {
    std::mt19937 mt(time(nullptr));
    m_coords.first = static_cast<int>(mt() % (width - 2)) + 1;
    m_coords.second = static_cast<int>(mt() % (height - 2)) + 1;
}

void Food::getEaten() {
    createNew(m_width, m_height);
}

void Food::draw() const {
    mvprintw(m_coords.second, m_coords.first, "X");
}

void Food::draw(WINDOW *win) const {
    mvwprintw(win, m_coords.second, m_coords.first, "X");
}

void Food::erase() const {
    mvprintw(m_coords.second, m_coords.first, " ");
}

void Food::erase(WINDOW *win) const {
    mvwprintw(win, m_coords.second, m_coords.first, " ");
}