#ifndef SNAKE_GAME_MENU_HPP
#define SNAKE_GAME_MENU_HPP

#include <ncurses.h>
#include <string>
#include <functional>
#include <vector>
#include <utility>

class Menu {
public:
    Menu() = default;
    explicit Menu(int numChoices) : m_numChoices(numChoices) {
        m_choices.resize(numChoices);
        m_actions.resize(numChoices);
    }
    ~Menu() = default;
    void setOption(int index, std::string choice, std::function<void()>&& action) {
        m_choices[index] = std::move(choice);
        m_actions[index] = action;
    }
    bool handleInput(int input) {
        switch (input) {
            case KEY_UP:
                m_highlight--;
                if (m_highlight == -1) {
                    m_highlight = m_numChoices - 1;
                }
                break;
            case KEY_DOWN:
                m_highlight++;
                if (m_highlight == m_numChoices) {
                    m_highlight = 0;
                }
                break;
            case 10:
                m_actions[m_highlight]();
                return true;
            default:
                break;
        }
        return false;
    }
    void draw(WINDOW *win, int startY, int startX) {
        for (int i = 0; i < m_numChoices; i++) {
            if (i == m_highlight) {
                wattron(win, A_REVERSE);
            }
            mvwprintw(win, startY + i, startX, "%s", m_choices[i].c_str());
            wattroff(win, A_REVERSE);
        }
        wrefresh(win);
    }

private:
    int m_highlight{};
    int m_numChoices{};
    std::vector<std::string> m_choices;
    std::vector<std::function<void()>> m_actions;
};

#endif //SNAKE_GAME_MENU_HPP
