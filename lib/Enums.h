#ifndef __LIB_ENUMS__
#define __LIB_ENUMS__

namespace lib {
    enum ElementType {
        Wall = 1,
        ImmuneWall = 2,
        SnakeHead = 3,
        SnakeBody = 4,
    };
    enum DirectionKey {
        up = 'w',
        left = 'a',
        right = 'd',
        down = 's'
    };
}

#endif