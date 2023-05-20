#ifdef _WIN32
#include <ncurses/ncurses.h>
#else
#include <ncurses.h>
#endif

namespace lib {
    class Window {
    private:
        WINDOW *window;
    
    public:
        Window(int height = 22, int width = 22, int startx = 0, int starty = 0);
        ~Window();
        
        WINDOW* getWindow();

        template<typename ... Types>
        void printw(int x, int y, const char* fnt, Types ... args);
        void printw(int x, int y, const char* fmt);

        void refresh();
    };
}