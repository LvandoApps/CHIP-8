#include <iostream>
#include <fstream>
#include "../include/chip8.h"

CHIP8::CHIP8() {
    pc = START_ADDRESS;
    // Load the fonts 0 through F into the memory of the CHIP8, starting at 0x050 and ending at 0x0A0 (80 bytes)
    for (int i = 0; i < SPRITE_SIZE; i++) {
        memory[SPRITE_START_ADDRESS + i] = sprite[i];
    }
}

CHIP8::~CHIP8() {}

void CHIP8::loadGame(char const* filename) {
    // Open the stream to binary and get the file pointer at the end of the file to get size efficiently before beginning
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    if (file.is_open()) {
        std::streampos filesize = file.tellg();
        // Return to the beginning of the file and store the contents of the file into a dynamic array of chars (dynamic to account for obvious changes in filesize)
        char* contents = new char[filesize];
        file.seekg(0, std::ios::beg);
        file.read(contents, filesize);
        file.close();
        // Load the now stored contents of the game into the memory of the CHIP8, starting at 0x200 (due to 0x000 - 0x1FF being reserved)
        for (long i = 0; i < filesize; i++) {
            memory[START_ADDRESS + i] = contents[i];
        }
        delete[] contents;
    }
    else {
        std::cout << "Error opening ROM" << std::endl;
    }
}

void CHIP8::INSTRUCT_00E0() {
    memset(display, 0, sizeof(display));
}

void CHIP8::INSTRUCT_00EE() {
    sp--;
    pc = stack[sp];
}

void CHIP8::INSTRUCT_1nnn() {
    uint16_t cur_address = instruction & nnn;
}

int main() {
    return EXIT_SUCCESS;
}