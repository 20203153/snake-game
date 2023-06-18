#include "AdditionalWindow.h"
#include "Maps.h"
#include "Snake.h"

void lib::ScoreboardWindow::refresh() {
    printw(1, 1, "Score Board");
    printw(2, 1, "B: %d / %d", snake->getLength(), 10);
    printw(3, 1, "+: %d", snake->getGrowthItemCount());
    printw(4, 1, "-: %d", snake->getPoisonItemCount());
    printw(5, 1, "G: %d", snake->getGateCount());
    printw(6, 1, "T: %d", map->getTicks() / 2);

    wrefresh(window);
    
    return;
}

void lib::MissionWindow::refresh() {
    auto it = missions.begin();
    bool completed = true;

    printw(1, 1, "Mission");
    for(int i = 1; it != missions.end(); it++, i++) {
        bool localCompleted = (*it).isCompleted(this->map, this->snake);
        printw(1 + i, 1, "%s: %d (%c)", (*it).title, (*it).goal, localCompleted ? 'v' : ' ');
        completed &= localCompleted;
    }
    this->completed = completed;
    wrefresh(window);

    return;
}