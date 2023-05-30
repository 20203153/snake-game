#include "Maps.h"
#include "Enums.h"
#include <cstring>
#include <memory>

using namespace lib;
using namespace std;

Map::Map(int (*map)[21], int sz): sz(sz), isContinue(true) {
    this->map = new int*[sz];
    
    for(int i = 0; i < sz; i++) {
        this->map[i] = new int[sz]{};
        memcpy(this->map[i], map[i], sizeof(int) * sz);
    }
}
Map::Map(const Map &v): sz(v.sz), isContinue(v.isContinue) {
    this->map = new int*[sz];

    for(int i = 0; i < sz; i++) {
        this->map[i] = new int[sz]{};
        memcpy(this->map[i], v.map[i], sizeof(int) * sz);
    }
}

/* Map::~Map() {
    for(int i = 0; i < sz; i++) {
        delete[] map[i];
    }
    delete[] map;
} */