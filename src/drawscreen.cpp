#include <iostream>
#include <SDL2/SDL.h>
#include "../include/drawscreen.h"

DRAWSCREEN::DRAWSCREEN(char const* title, int screen_height, int screen_width, int texture_height, int texture_width) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        sdlWork = false;
    }
    window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        screen_height,
        screen_width,
        SDL_WINDOW_ALLOW_HIGHDPI
    );
    renderer = SDL_CreateRenderer(
        window, 
        -1, 
        SDL_RENDERER_ACCELERATED
    );
    texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_STREAMING,
        texture_height,
        texture_width
    );

}

DRAWSCREEN::~DRAWSCREEN() {
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void DRAWSCREEN::Update(void const* buffer, int pitch) {
    SDL_UpdateTexture(texture, nullptr, buffer, pitch);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
    SDL_RenderPresent(renderer);
}