#include "wall.hpp"
#include <random>
#include <utility>
#include <algorithm>

Wall::Wall(std::vector<coords_t>& walls) : m_walls(std::move(walls)) {}

bool Wall::isWall(const coords_t& coords) const {
    return std::find(m_walls.begin(), m_walls.end(), coords) != m_walls.end();
}

void Wall::addWall(const coords_t& coords) {
    m_walls.emplace_back(coords);
}

void Wall::generateRandomWall(int width, int height) {
    std::random_device rd;
    std::mt19937 mt(rd());
    coords_t coords;
    coords.first = static_cast<int>(mt() % (width - 2)) + 1;
    coords.second = static_cast<int>(mt() % (height - 2)) + 1;

    addWall(coords);
}

void Wall::draw() const {
    for (const auto &coords : m_walls) {
        mvprintw(coords.second, coords.first, "#");
    }
}

void Wall::draw(WINDOW *win) const {
    for (const auto &coords : m_walls) {
        mvwprintw(win, coords.second, coords.first, "#");
    }
}