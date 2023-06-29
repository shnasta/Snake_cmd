#include "states/mainmenu_state.hpp"
#include "states/play_state.hpp"
#include <filesystem>

MainMenuState& MainMenuState::getInstance() {
    static MainMenuState instance;
    return instance;
}

void MainMenuState::enter(SnakeGame* game) {
    nodelay(stdscr, FALSE);
    m_win = game->getWindow();
    game->printBorder();
    refresh();
    wrefresh(m_win);

    initMainMenu(game);
    initSettingsMenu(game);
    initLevelsMenu(game);

    m_currentMenu = &m_mainMenu;
}

void MainMenuState::exit(SnakeGame* game) {
    wclear(m_win);
    clear();
    refresh();
    wrefresh(m_win);
}

void MainMenuState::execute(SnakeGame* game) {
    int choice;
    m_currentMenu->draw(m_win, 1, 1);

    choice = getch();
    m_currentMenu->handleInput(choice);
}

void MainMenuState::initMainMenu(SnakeGame* game) {
    m_mainMenu = Menu(4);
    m_mainMenu.setOption(0, "Start", [&, game]() {
        game->setCurrentLevel("");
        game->setState(PlayState::getInstance());
    });
    m_mainMenu.setOption(1, "Levels", [&, game]() {
        m_currentMenu = &m_levelsMenu;
        wclear(m_win);
        game->printBorder();
    });
    m_mainMenu.setOption(2, "View Settings", [&, game]() {
        m_currentMenu = &m_settingsMenu;
        wclear(m_win);
        game->printBorder();
    });
    m_mainMenu.setOption(3, "Exit", [&, game]() {
        game->exit();
    });
}

void MainMenuState::initSettingsMenu(SnakeGame* game) {
    m_settingsMenu = Menu(3);
    m_settingsMenu.setOption(0, "Back", [&, game] () {
        m_currentMenu = &m_mainMenu;
        wclear(m_win);
        game->printBorder();
    });
    m_settingsMenu.setOption(1, "Border", [&, game]() {
        game->toggleBorder();
    });
    m_settingsMenu.setOption(2, "Centralize", [&, game]() {
        wclear(m_win);
        clear();
        refresh();
        game->toggleCentered();
        game->printBorder();
        refresh();
    });
}

void MainMenuState::initLevelsMenu(SnakeGame *game) {
    namespace fs = std::filesystem;
    auto levelsPath = game->getLevelsPath();
    int numLevels = static_cast<int>(std::distance(fs::directory_iterator(levelsPath), std::filesystem::directory_iterator{}));

    m_levelsMenu = Menu(numLevels + 1);
    m_levelsMenu.setOption(0, "Back", [&, game]() {
        m_currentMenu = &m_mainMenu;
        wclear(m_win);
        game->printBorder();
    });

    int countOpt = 1;
    for (const auto& entry : fs::directory_iterator(levelsPath)) {
        auto levelName = entry.path().filename().string();
        auto rawName = levelName.substr(0, levelName.find_last_of('.'));
        m_levelsMenu.setOption(countOpt, rawName, [&, game, levelName]() {
            game->setCurrentLevel(levelName);
            game->setState(PlayState::getInstance());
        });
        countOpt++;
    }
}
