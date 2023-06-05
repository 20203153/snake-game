#include <iostream>
#include <unistd.h>
#include <ctime>
#include "lib/Window.h"
#include "lib/Maps.h"
#include "lib/Snake.h"

#ifdef _WIN32
#include <ncurses/ncurses.h>
#else
#include <ncurses.h>
#endif

using namespace std;
using namespace lib;

int mapData_1[21][21] = {
    { 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2 },
};

void getMap(Map &map, Snake &snake) {
    int mapSz = 21;
    int SnakeBody[6] = {10, 10, 11, 10, 12, 10};
    map = Map(mapData_1, mapSz);
    snake = Snake(SnakeBody, 6);
    
    return;
}

int main() {
    initscr();
    timeout(0);
    curs_set(false);
    noecho();
    refresh();
    start_color();

    srand(time(NULL));

    init_pair(10, COLOR_BLACK, COLOR_WHITE);
    init_pair(ElementType::Wall, COLOR_GREEN, COLOR_CYAN);
    init_pair(ElementType::ImmuneWall, COLOR_WHITE, COLOR_BLUE);
    init_pair(ElementType::SnakeHead, COLOR_WHITE, COLOR_RED);
    init_pair(ElementType::SnakeBody, COLOR_WHITE, COLOR_MAGENTA);
    init_pair(ElementType::GrowthItem, COLOR_WHITE, COLOR_GREEN);
    init_pair(ElementType::PoisonItem, COLOR_WHITE, COLOR_BLACK);
    

    int startx = (COLS - (21 * 2) + 2) / 2;
    int starty = (LINES - 21 + 2) / 2;

    int SnakeBody[6] = {10, 10, 11, 10, 12, 10};
    Map map1(mapData_1, 21);
    Snake snake(SnakeBody, 3);

    MainWindow mainWindow(&map1, startx, starty);
    snake.draw(&map1);
    mainWindow.printMap();

    while(map1.isContinue) {
        usleep(500 * 1000);
        char v = getch();
        snake.move(v);
        snake.draw(&map1);
        mainWindow.printMap();
        mainWindow.printw(22, 0, "Continue! %d", (map1.getTicks()) / 2);
    }

    mainWindow.printw(11, 15, "Game Over!");
    getch();
    mainWindow.~MainWindow();
    endwin();

    return 0;
}