#ifndef SNAKE_GAME_SNAKE_HPP
#define SNAKE_GAME_SNAKE_HPP

#include <utility>
#include <vector>

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Snake {
    using coords_t = std::pair<int, int>;

    coords_t m_head;
    int m_length = 3;
    std::vector<coords_t> m_body;
    Direction m_direction = Direction::UP;

    [[nodiscard]] bool isSnake(coords_t coords) const;
public:
    Snake(int startX, int startY);
    ~Snake() = default;

    [[nodiscard]] int getX() const { return m_head.first; }
    [[nodiscard]] int getY() const { return m_head.second; }
    [[nodiscard]] int getLength() const { return m_length; }
    [[nodiscard]] Direction getDirection() const { return m_direction; }

    coords_t predictMove();
    void move();
    void moveAndGrow();
    void setDirection(Direction direction);
    void draw() const;
    void draw(WINDOW *win) const;
    void erase() const;

    void debugPrint() const;

    void erase(WINDOW *win) const;
};


#endif //SNAKE_GAME_SNAKE_HPP
