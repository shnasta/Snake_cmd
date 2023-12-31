#ifndef SNAKE_GAME_PLAY_STATE_HPP
#define SNAKE_GAME_PLAY_STATE_HPP

#include "basic_state.hpp"
#include "snake_game.hpp"
#include "snake.hpp"
#include "food.hpp"
#include "wall.hpp"

class PlayState : public BasicState<SnakeGame> {
    using coords_t = std::pair<int, int>;
public:
    void enter(SnakeGame*) override;
    void exit(SnakeGame*) override;
    void execute(SnakeGame*) override;
    static PlayState& getInstance();
private:
    WINDOW *m_win{};
    WINDOW *m_gameWin{};
    Snake m_snake{};
    Food m_food{};
    Wall m_wall{};
    int m_score{};
    int m_width = 30;
    int m_height = 15;
    int m_generalWidth{};
    int m_generalHeight{};

    int DELAY = 300;
    bool m_gameOver = false;
    bool m_pause = false;

    void makeMove();

    void checkForTeleport(coords_t &nextMove) const;

    void checkInputForQP(int ch);

    void checkInputForMove(int ch);

    void draw() const;

    void drawScore() const;

    void readLevel(const std::string &levelPath);

    void defaultLevel();

    void makeFood();

    void drawInstruct() const;
};

#endif //SNAKE_GAME_PLAY_STATE_HPP
