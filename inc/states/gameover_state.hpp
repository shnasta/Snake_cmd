#ifndef SNAKE_GAME_GAMEOVER_STATE_HPP
#define SNAKE_GAME_GAMEOVER_STATE_HPP

#include "basic_state.hpp"
#include "snake_game.hpp"
#include "utils/menu.hpp"

class GameOverState : public BasicState<SnakeGame> {
public:
    void enter(SnakeGame*) override;
    void exit(SnakeGame*) override;
    void execute(SnakeGame*) override;
    static GameOverState& getInstance();
private:
    WINDOW *m_win{};
    int m_score{};
    int m_highScore{};
    Menu m_menu{};
    void initMenu(SnakeGame* game);
};

#endif //SNAKE_GAME_GAMEOVER_STATE_HPP
