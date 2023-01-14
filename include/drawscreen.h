#include <stdint.h>

const unsigned int WINDOW_HEIGHT = 640;
const unsigned int WINDOW_WIDTH = 1280;

class DRAWSCREEN {
    public:
        SDL_Window* window = nullptr;
        SDL_Renderer* renderer = nullptr;
        bool sdlWork = true;

    public:
        DRAWSCREEN(char const* title, int screenHeight, int screenWidth, int textureHeight, int textureWidth);
        ~DRAWSCREEN();
        void Update();
        bool Process();

};