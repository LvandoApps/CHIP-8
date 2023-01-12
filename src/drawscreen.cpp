#include <iostream>
#include <SDL2/SDL.h>
#include "../include/drawscreen.h"

DRAWSCREEN::DRAWSCREEN() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        sdlWork = false;
    }
    window = SDL_CreateWindow(
        "LvandoApps Emulator",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_HEIGHT,
        WINDOW_WIDTH,
        SDL_WINDOW_ALLOW_HIGHDPI
    );
}

DRAWSCREEN::~DRAWSCREEN() {

}

int main() {
    
}