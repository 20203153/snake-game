#include "Enums.h"

#ifndef __LIB_MAPS__
#define __LIB_MAPS__

using namespace lib;

namespace lib {
    class Map {
    public:
        bool isContinue;
        int sz;
        int** map;
        Map(int (*map)[21], int sz);
        Map(const Map &v);
        Map() {}
        // ~Map();
    };
}

#endif