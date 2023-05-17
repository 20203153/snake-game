#include <iostream>
#include <ncurses.h>
#include "lib/Window.h"

using namespace std;
using namespace lib;

int main() {
    initscr();
    refresh();

    Window mainWindow;

    WINDOW* mainW = mainWindow.getWindow();

    mvwprintw(mainW, 1, 1, "Hello World!");
    wrefresh(mainW);

    getch();
    mainWindow.~Window();
    endwin();

    return 0;
}