#include <stdint.h>
#include <SDL2/SDL.h>

class DRAWSCREEN {
    public:
        // Required features for SDL
        SDL_Window* window = nullptr;
        SDL_Renderer* renderer = nullptr;
        SDL_Texture* texture = nullptr;

    public:
        DRAWSCREEN(char const* title, int screenHeight, int screenWidth, int textureHeight, int textureWidth);
        ~DRAWSCREEN();
        void Update(void const* buffer, int pitch);
        bool Process(uint8_t* keys);

};