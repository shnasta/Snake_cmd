#ifndef SNAKE_GAME_PLAY_STATE_HPP
#define SNAKE_GAME_PLAY_STATE_HPP

#include "basic_state.hpp"
#include "snake_game.hpp"
#include "snake.hpp"
#include "food.hpp"

class PlayState : public BasicState<SnakeGame> {
    using coords_t = std::pair<int, int>;
public:
    void enter(SnakeGame*) override;
    void exit(SnakeGame*) override;
    void execute(SnakeGame*) override;
    static PlayState& getInstance();
private:
    WINDOW *m_win{};
    Snake m_snake{};
    Food m_food{};
    char m_input{};
    int m_score{};
    int m_width{};
    int m_height{};

    int DELAY = 300;
    bool m_gameOver = false;

    void makeMove();

    void checkForTeleport(coords_t &nextMove) const;

    void checkInput();

    void draw() const;

    void drawScore() const;
};

#endif //SNAKE_GAME_PLAY_STATE_HPP
