#include <iostream>
#include "lib/Window.h"
#include "lib/Maps.h"

#ifdef _WIN32
#include <ncurses/ncurses.h>
#else
#include <ncurses.h>
#endif

using namespace std;
using namespace lib;

int main() {
    initscr();
    refresh();
    start_color();

    init_pair(10, COLOR_BLACK, COLOR_WHITE);
    init_pair(ElementType::Wall, COLOR_GREEN, COLOR_CYAN);
    init_pair(ElementType::ImmuneWall, COLOR_WHITE, COLOR_CYAN);
    init_pair(ElementType::SnakeHead, COLOR_WHITE, COLOR_RED);
    init_pair(ElementType::SnakeBody, COLOR_WHITE, COLOR_MAGENTA);

    int startx = (COLS - 23) / 2;
    int starty = (LINES - 23) / 2;

    Maps::Map map1 = Maps::getMap();
    MainWindow mainWindow(map1, startx, starty);

    mainWindow.printMap();

    getch();
    mainWindow.~MainWindow();
    endwin();

    return 0;
}