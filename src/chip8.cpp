#include <iostream>
#include <fstream>
#include "../include/chip8.h"

CHIP8::CHIP8() {
    pc = START_ADDRESS;
}

CHIP8::~CHIP8() {

}

void CHIP8::loadGame(char const* filename) {
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    if (file.is_open()) {
        std::streampos filesize = file.tellg();
        char* buffer = new char[filesize];
        file.seekg(0, std::ios::beg);
        file.read(buffer, filesize);
        file.close();
        for (long i = 0; i < filesize; i++) {
            memory[START_ADDRESS + i] = buffer[i];
        }
        delete[] buffer;
    }
    else {
        std::cout << "Error opening ROM" << std::endl;
    }
}

int main() {
    return EXIT_SUCCESS;
}