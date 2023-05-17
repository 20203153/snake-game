#include <ncurses.h>

namespace lib {
    class Window {
    private:
        WINDOW *window;
    
    public:
        Window(int height = 22, int width = 22);
        ~Window();
        
        WINDOW* getWindow();
    };
}