#ifndef SNAKE_GAME_FOOD_HPP
#define SNAKE_GAME_FOOD_HPP

#include <utility>
#include <ncurses.h>

class Food {
    using coords_t = std::pair<int, int>;
public:
    Food() = default;
    Food(int width, int height);

    [[nodiscard]] int getX() const { return m_coords.first; }
    [[nodiscard]] int getY() const { return m_coords.second; }
    [[nodiscard]] coords_t getCoords() const { return m_coords; }
    [[nodiscard]] bool isFood(coords_t coords) const { return m_coords == coords; }

    void createNew(int width, int height);
    void getEaten();

    void draw() const;
    void draw(WINDOW *win) const;
    void erase() const;
    void erase(WINDOW *win) const;
private:
    coords_t m_coords;
    int m_width;
    int m_height;
};

#endif //SNAKE_GAME_FOOD_HPP
