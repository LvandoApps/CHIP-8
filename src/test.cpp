#include <iostream>
#include "../src/include/SDL2/SDL.h"

int main() {
    std::cout << "yes" << std::endl;
    std::cout << SDL_Init(SDL_INIT_VIDEO) << std::endl;
    return EXIT_SUCCESS;
}