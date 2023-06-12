#include "AdditionalWindow.h"
#include "Maps.h"
#include "Snake.h"

void lib::ScoreboardWindow::refresh() {
    printw(1, 1, "Score Board");
    printw(2, 1, "B: %d / %d", snake->getLength(), 10);
    printw(3, 1, "+: %d", 0);
    printw(4, 1, "-: %d", 0);
    printw(5, 1, "G: %d", 0);
    printw(6, 1, "T: %d", map->getTicks() / 2);

    wrefresh(window);
    
    return;
}