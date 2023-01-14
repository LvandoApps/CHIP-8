#include <stdint.h>

class DRAWSCREEN {
    public:
        SDL_Window* window = nullptr;
        SDL_Renderer* renderer = nullptr;
        SDL_Texture* texture = nullptr;
        bool sdlWork = true;

    public:
        DRAWSCREEN(char const* title, int screenHeight, int screenWidth, int textureHeight, int textureWidth);
        ~DRAWSCREEN();
        void Update(void const* buffer, int pitch);
        bool Process(uint8_t* keys);

};