#include "Window.h"
#include <ncurses.h>

namespace lib {
    Window::Window(int height, int width) {
        int startx, starty;

        startx = (COLS - width) / 2;
        starty = (LINES - height) / 2;

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
}