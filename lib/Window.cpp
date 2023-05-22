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
        wrefresh(window);
        delwin(window);
    }

    WINDOW* Window::getWindow() {
        return window;
    }

    template <typename ... Types>
    void Window::printw(int x, int y, const char *fmt, Types ... args) {
        mvwprintw(window, x, y, fmt, args...);
    }
    void Window::printw(int x, int y, const char *fmt) {
        mvwprintw(window, x, y, fmt);
    }

    void Window::refresh() {
        wrefresh(window);
    }

    void MainWindow::printMap() {
        for(int i = 0; i < map.sz; i++) {
            for(int j = 0; j < map.sz; j++) {
                switch(map.Map[i][j]) {
                    case ElementType::ImmuneWall:
                        mvwaddch(window, 1 + j, 1 + i, (chtype)('X' | COLOR_PAIR(ElementType::ImmuneWall)));
                        break;
                    case ElementType::Wall:
                        mvwaddch(window, 1 + j, 1 + i, (chtype)('I' | COLOR_PAIR(ElementType::Wall)));
                        break;
                    case ElementType::SnakeHead:
                        mvwaddch(window, 1 + j, 1 + i, (chtype)('O' | COLOR_PAIR(ElementType::SnakeHead)));
                        break;
                    case ElementType::SnakeBody:
                        mvwaddch(window, 1 + j, 1 + i, (chtype)('A' | COLOR_PAIR(ElementType::SnakeBody)));
                        break;
                    default:
                        mvwaddch(window, 1 + j, 1 + i, (chtype)(' ' | COLOR_PAIR(10)));
                }
            }
        }
        refresh();
    }
}