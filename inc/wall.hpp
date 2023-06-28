#ifndef SNAKE_GAME_WALL_HPP
#define SNAKE_GAME_WALL_HPP

#include <ncurses.h>
#include <vector>

class Wall {
    using coords_t = std::pair<int, int>;
public:
    Wall() = default;
    Wall(std::vector<coords_t>& walls);
    ~Wall() = default;

    [[nodiscard]] bool isWall(coords_t& coords) const;
    void addWall(const coords_t& coords);
    void generateRandomWall(int width, int height);

    void draw() const;
    void draw(WINDOW *win) const;
    void erase() const;
    void erase(WINDOW *win) const;
private:
    std::vector<coords_t> m_walls;
};

#endif //SNAKE_GAME_WALL_HPP
