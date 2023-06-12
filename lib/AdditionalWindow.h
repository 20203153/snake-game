#include "Window.h"
#include "Maps.h"
#include "Snake.h"

#ifndef __WINDOWS__
#define __WINDOWS__

namespace lib {
    class ScoreboardWindow : public Window {
        Map *map;
        Snake *snake;

    public:
        ScoreboardWindow(int startx, int starty, Map *map, Snake *snake): Window(12, 16, startx, starty), map(map), snake(snake) {}
        void refresh();

        ~ScoreboardWindow() {
            delwin(window);
        }
    };

    class ArchiveWindow : public Window {
        Map *map;
        Snake *snake;

    public:
        ArchiveWindow(int x, int y, int startx, int starty, Map *map, Snake *snake): Window(x, y, startx, starty), map(map), snake(snake) {}
        void refresh();

        ~ArchiveWindow() {
            delwin(window);
        }
    };
}

#endif