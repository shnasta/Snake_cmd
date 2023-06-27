#ifndef SNAKE_GAME_MAINMENU_STATE_HPP
#define SNAKE_GAME_MAINMENU_STATE_HPP

#include "basic_state.hpp"
#include "snake_game.hpp"

class MainMenuState : public BasicState<SnakeGame> {
public:
    void enter(SnakeGame*) override;
    void exit(SnakeGame*) override;
    void execute(SnakeGame*) override;
    static MainMenuState& getInstance();
private:
    WINDOW *m_win{};
};



#endif //SNAKE_GAME_MAINMENU_STATE_HPP
