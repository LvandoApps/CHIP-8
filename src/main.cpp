#include <iostream>
#include <chrono>
#include "../include/drawscreen.h"
#include "../include/chip8.h"

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "The command you entered is not valid, here is the correct command format:" << std::endl;
        std::cerr << argv[0] << "<Scale> <Delay> <ROMFileName>" << std::endl;
        return EXIT_FAILURE;
    }
    int display_scale = std::stoi(argv[1]);
    int cycle_delay = std::stoi(argv[2]);
    char const* rom_file_name = argv[3];

    bool sdlWork = true;
    DRAWSCREEN screen(
        sdlWork,
        "LvandoApps CHIP-8 Emulator",
        DISPLAY_WIDTH * display_scale,
        DISPLAY_HEIGHT * display_scale,
        DISPLAY_WIDTH,
        DISPLAY_HEIGHT);
    
    if (sdlWork == false) {
        std::cerr << "ERROR: SDL could not be commenced. Please ensure SDL library is included correctly. Exiting safely.." << std::endl;
        return EXIT_FAILURE;
    }

    CHIP8 emulator;
    bool check_validity = true;
    emulator.loadGame(rom_file_name, check_validity);
    if (check_validity == false) {
        std::cerr << "ERROR: Game could not be loaded. Please ensure the filename you entered is correct. Exiting safely.." << std::endl;
        return EXIT_FAILURE;
    }


    return EXIT_SUCCESS;
}