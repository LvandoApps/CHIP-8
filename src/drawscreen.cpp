#include <iostream>
#include <SDL2/SDL.h>
#include "../include/drawscreen.h"

DRAWSCREEN::DRAWSCREEN(char const* title, int screen_width, int screen_height, int texture_width, int texture_height) {
    // Here we initialise the window, renderer, as well as texture. Using texture is a better alternative than just using the renderer
    // as it will allow me to update and draw the pixel in a single step later on rather than updating the buffer THEN drawing the pixels to the screen
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        screen_width,
        screen_height,
        SDL_WINDOW_SHOWN
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
        texture_width,
        texture_height
    );
    // We set the renderer to a default of black, clear whatever render is there (if any), and present the black screen. This isn't really needed
    // but is more of an insurance policy if something for some reason went wrong
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

DRAWSCREEN::~DRAWSCREEN() {
    // Here we destroy everything and quit, no need to reset values as this is done in the headerfile on program startup
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void DRAWSCREEN::Update(void const* buffer, int pitch) {
    // Set the texture to be white and ensure no blending before updating the texture (i.e putting the pixel onto the screen
    // after being informed by Dxyn instruction)
    SDL_SetTextureColorMod(texture, 255, 255, 255);
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_NONE);
    // Now we update the contents of a texture with new pixel data from Dxyn, clear current rendering target
    // with black (as defined before), copy a portion of the texture containing the new pixel data to the current rendering
    // target, then finally update the screen with any rendering that was done, making the pixel data
    // now visible on the screen
    SDL_UpdateTexture(texture, nullptr, buffer, pitch);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
    SDL_RenderPresent(renderer);
}

bool DRAWSCREEN::Process(uint8_t* keys) {
    bool quit = false;
    SDL_Event event;
    // SDL process method that loops while the game is running and continues to poll events done by the player, converting
    // those events (keypresses) into the correct outputs
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        quit = true;
                        break;

                    case SDLK_x:
                        keys[0] = 1;
                        break;

                    case SDLK_1:
                        keys[1] = 1;
                        break;

                    case SDLK_2:
                        keys[2] = 1;
                        break;

                    case SDLK_3:
                        keys[3] = 1;
                        break;

                    case SDLK_q:
                        keys[4] = 1;
                        break;

                    case SDLK_w:
                        keys[5] = 1;
                        break;

                    case SDLK_e:
                        keys[6] = 1;
                        break;

                    case SDLK_a:
                        keys[7] = 1;
                        break;

                    case SDLK_s:
                        keys[8] = 1;
                        break;

                    case SDLK_d:
                        keys[9] = 1;
                        break;

                    case SDLK_z:
                        keys[0xA] = 1;
                        break;

                    case SDLK_c:
                        keys[0xB] = 1;
                        break;

                    case SDLK_4:
                        keys[0xC] = 1;
                        break;

                    case SDLK_r:
                        keys[0xD] = 1;
                        break;

                    case SDLK_f:
                        keys[0xE] = 1;
                        break;

                    case SDLK_v:
                        keys[0xF] = 1;
                        break;
                }
                break;

            case SDL_KEYUP:
                switch (event.key.keysym.sym) {
                    case SDLK_x:
                        keys[0] = 0;
                        break;

                    case SDLK_1:
                        keys[1] = 0;
                        break;

                    case SDLK_2:
                        keys[2] = 0;
                        break;

                    case SDLK_3:
                        keys[3] = 0;
                        break;

                    case SDLK_q:
                        keys[4] = 0;
                        break;

                    case SDLK_w:
                        keys[5] = 0;
                        break;

                    case SDLK_e:
                        keys[6] = 0;
                        break;

                    case SDLK_a:
                        keys[7] = 0;
                        break;

                    case SDLK_s:
                        keys[8] = 0;
                        break;

                    case SDLK_d:
                        keys[9] = 0;
                        break;

                    case SDLK_z:
                        keys[0xA] = 0;
                        break;

                    case SDLK_c:
                        keys[0xB] = 0;
                        break;

                    case SDLK_4:
                        keys[0xC] = 0;
                        break;

                    case SDLK_r:
                        keys[0xD] = 0;
                        break;

                    case SDLK_f:
                        keys[0xE] = 0;
                        break;

                    case SDLK_v:
                        keys[0xF] = 0;
                        break;
                }
        } 
        break;
    }
    return quit;
}