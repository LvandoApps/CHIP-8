#include <iostream>
#include <SDL2/SDL.h>
#include "../include/drawscreen.h"

DRAWSCREEN::DRAWSCREEN(char const* title, int screenHeight, int screenWidth, int textureHeight, int textureWidth) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        sdlWork = false;
    }
    window = SDL_CreateWindow(
        "LvandoApps CHIP-8 Emulator",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_HEIGHT,
        WINDOW_WIDTH,
        SDL_WINDOW_ALLOW_HIGHDPI
    );

}

DRAWSCREEN::~DRAWSCREEN() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

int main() {
    
}