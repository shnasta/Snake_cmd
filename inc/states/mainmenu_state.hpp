#ifndef SNAKE_GAME_MAINMENU_STATE_HPP
#define SNAKE_GAME_MAINMENU_STATE_HPP

#include "basic_state.hpp"
#include "snake_game.hpp"
#include "utils/menu.hpp"
#include <string>

class MainMenuState : public BasicState<SnakeGame> {
public:
    void enter(SnakeGame*) override;
    void exit(SnakeGame*) override;
    void execute(SnakeGame*) override;
    static MainMenuState& getInstance();
private:
    WINDOW *m_win{};
    Menu m_mainMenu{};
    Menu m_settingsMenu{};
    Menu m_levelsMenu{};
    Menu* m_currentMenu = nullptr;

    void initMainMenu(SnakeGame* game);
    void initSettingsMenu(SnakeGame* game);
    void initLevelsMenu(SnakeGame* game);
};



#endif //SNAKE_GAME_MAINMENU_STATE_HPP
