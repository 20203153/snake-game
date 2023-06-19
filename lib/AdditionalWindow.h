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
        ScoreboardWindow(int startx, int starty, Map *map, Snake *snake): Window(11, 16, startx, starty), map(map), snake(snake) {}
        ScoreboardWindow(int startx = 0, int starty = 0): Window(11, 16, startx, starty) {
            wresize(window, width, height);
            wmove(window, starty, startx);
        }
        void refresh();

        ~ScoreboardWindow() {
            delwin(window);
        }
    };

    struct MissionData {
        char title[5];
        int goal;
        bool (*isCompleted)(Map *map, Snake *snake);
    };

    class MissionWindow : public Window {
        Map *map;
        Snake *snake;
        std::vector<MissionData> missions;
        bool completed;

    public:
        MissionWindow(int startx, int starty, Map *map, Snake *snake, std::vector<MissionData> missions):
            Window(11, 16, startx, starty), map(map), snake(snake), missions(missions) {}
        MissionWindow(int startx = 0, int starty = 0): Window(11, 16, startx, starty) {
            wresize(window, width, height);
            wmove(window, starty, startx);
        }
        void refresh();
        bool isComplete() { return completed; };

        ~MissionWindow() {
            delwin(window);
        }
        void setMissions(std::vector<MissionData> missions) { this->missions = missions; return; }
    };
}

#endif