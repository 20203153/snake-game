#include "Window.h"

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
}