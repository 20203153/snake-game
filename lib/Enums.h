#ifdef _WIN32
#include <ncurses/ncurses.h>
#else
#include <ncurses.h>
#endif

#ifndef __LIB_ENUMS__
#define __LIB_ENUMS__

namespace lib {
    enum ElementType {
        Wall = 1,
        ImmuneWall = 2,
        SnakeHead = 3,
        SnakeBody = 4,
        GrowthItem = 5,
        PoisonItem = 6,
        Gate = 7
    };
    enum DirectionKey {
        up = 'w',
        left = 'a',
        right = 'd',
        down = 's'
    };
}

#endif