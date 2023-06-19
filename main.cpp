#include <iostream>
#include <unistd.h>
#include <ctime>
#include "lib/Window.h"
#include "lib/Maps.h"
#include "lib/Snake.h"
#include "lib/AdditionalWindow.h"
#include "lib/GetStage.h"

#ifdef _WIN32
#include <ncurses/ncurses.h>
#else
#include <ncurses.h>
#endif

using namespace std;
using namespace lib;

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
    init_pair(ElementType::Gate, COLOR_WHITE, COLOR_BLUE);

    bool isGameover = false;

    for(int i = 0; i < 1; i++) {
        Map map;
        Snake snake;
        vector<MissionData> missionData;
        for(int stage_count = 1; stage_count < 5; stage_count++) {
            getStage(stage_count, map, snake, missionData);

            int startx = (COLS - (map.sz * 2) - 16) / 2;
            int starty = (LINES - map.sz + 2) / 2;

            MainWindow mainWindow(&map, startx, starty);
            snake.draw(&map);
            mainWindow.printMap();
            
            ScoreboardWindow sWindow(startx + (map.sz * 2) + 4, starty, &map, &snake);
            sWindow.refresh();
            
            MissionWindow mWindow(startx + (map.sz * 2) + 4, starty + 12, &map, &snake, missionData);
            mWindow.refresh();

            while(map.isContinue && !mWindow.isComplete()) {
                usleep(500 * 1000);
                char v = getch();
                snake.move(v);
                snake.draw(&map);
                mainWindow.printMap();
                sWindow.refresh();
                mWindow.refresh();
            }
            if(!mWindow.isComplete()) {
                isGameover = true;
                break;
            }

            Window window(5, 20, (COLS - 20) / 2, (LINES - 5) / 2);
            window.printw(2, 3, "Map Complete!");
            window.refresh();
            usleep(3000 * 1000);
            window.~Window();
            map.destroy();
        }
    }

    while(isGameover) {
        Window window(5, 20, (COLS - 20) / 2, (LINES - 5) / 2);
        window.printw(1, 5, "Game Over!");
        window.printw(3, 4, "End to Ctrl+C");
        window.refresh();

        usleep(500 * 1000);
    }

    while(true) {
        Window window(5, 20, (COLS - 20) / 2, (LINES - 5) / 2);
        window.printw(1, 3, "Game Complete!");
        window.printw(3, 4, "End to Ctrl+C");
        window.refresh();
        usleep(500 * 1000);
        window.~Window();
    }

    refresh();
    endwin();

    return 0;
}