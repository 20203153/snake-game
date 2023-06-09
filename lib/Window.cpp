#include "Window.h"
#include "Enums.h"
#include <string>

#ifdef _WIN32
#include <ncurses/ncurses.h>
#else
#include <ncurses.h>
#endif

namespace lib {
    Window::Window(int height, int width, int startx, int starty) {
        window = newwin(height, width, starty, startx);
        box(window, 0, 0);
        wrefresh(window);

        return;
    }

    Window::~Window() {
        delwin(window);
    }

    WINDOW* Window::getWindow() {
        return window;
    }

    void MainWindow::printMap() {
        chtype str[3] = { ' ', ' ', 0 };
        for(int i = 0; i < map->sz; i++) {
            for(int j = 0; j < map->sz; j++) {
                switch(map->map[i][j]) {
                    case ElementType::ImmuneWall:
                        str[0] = str[1] = ' '|COLOR_PAIR(ElementType::ImmuneWall);
                        mvwaddchstr(window, 1 + j, 1 + i * 2, str);
                        break;
                    case ElementType::Wall:
                        str[0] = str[1] = ' ' | COLOR_PAIR(ElementType::Wall);
                        mvwaddchstr(window, 1 + j, 1 + i * 2, str);
                        break;
                    case ElementType::SnakeHead:
                        str[0] = str[1] = ' ' | COLOR_PAIR(ElementType::SnakeHead);
                        mvwaddchstr(window, 1 + j, 1 + i * 2, str);
                        break;
                    case ElementType::SnakeBody:
                        str[0] = str[1] = ' ' | COLOR_PAIR(ElementType::SnakeBody);
                        mvwaddchstr(window, 1 + j, 1 + i * 2, str);
                        break;
                    case ElementType::GrowthItem:
                        str[0] = str[1] = ' ' | COLOR_PAIR(ElementType::GrowthItem);
                        mvwaddchstr(window, 1 + j, 1 + i * 2, str);
                        break;
                    case ElementType::PoisonItem:
                        str[0] = str[1] = 'X' | COLOR_PAIR(ElementType::PoisonItem);
                        mvwaddchstr(window, 1 + j, 1 + i * 2, str);
                        break;
                    case ElementType::Gate:
                        str[0] = str[1] = 'G' | COLOR_PAIR(ElementType::Gate);
                        mvwaddchstr(window, 1 + j, 1 + i * 2, str);
                        break;
                    default:
                        str[0] = str[1] = ' ' | COLOR_PAIR(10);
                }
                mvwaddchstr(window, 1 + j, 1 + i * 2, str);
            }
        }

        wrefresh(window);
    }
}