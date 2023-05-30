#ifdef _WIN32
#include <ncurses/ncurses.h>
#else
#include <ncurses.h>
#endif

#include "Maps.h"

#ifndef __LIB_WINDOWS__
#define __LIB_WINDOWS__

namespace lib {
    class Window {
    protected:
        WINDOW *window;
    
    public:
        Window(int height = 22, int width = 22, int startx = 0, int starty = 0);
        ~Window();
        
        WINDOW* getWindow();

        void printw(int x, int y, const char *fmt) {
            mvwprintw(window, x, y, fmt);
        }

        template <typename ...Types>
        void printw(int x, int y, const char *fmt, Types... args) {
            mvwprintw(window, x, y, fmt, args...);
        }

        void refresh();
    };

    class MainWindow : public Window {
    private:
        int height;
        int width;
        int startx;
        int starty;
        Map *map;
    public:
        MainWindow(Map *map, int startx = 0, int starty = 0): map(map), Window(map->sz + 2, map->sz * 2 + 2, startx, starty) {

        };
        void printMap();
    };
}

#endif