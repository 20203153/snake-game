#include <iostream>
#include <ncurses.h>
#include "lib/Window.h"

using namespace std;
using namespace lib;

int main() {
    initscr();
    refresh();

    int startx = (COLS - 22) / 2;
    int starty = (LINES - 22) / 2;

    Window mainWindow(22, 22, startx, starty);

    mainWindow.printw(1, 1, "Hello World!");
    mainWindow.refresh();

    getch();
    mainWindow.~Window();
    endwin();

    return 0;
}