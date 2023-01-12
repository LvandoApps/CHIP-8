#include <stdint.h>

const unsigned int WINDOW_HEIGHT = 640;
const unsigned int WINDOW_WIDTH = 1280;

class DRAWSCREEN {
    public:
        SDL_Window* window = nullptr;
        SDL_Renderer* renderer = nullptr;
        bool sdlWork = true;

    public:
        DRAWSCREEN();
        ~DRAWSCREEN();

};