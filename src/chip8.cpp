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

// Clear the display.
void CHIP8::INSTRUCT_00E0() {
    memset(display, 0, sizeof(display));
}

// Return from a subroutine.
// The interpreter sets the program counter to the address at the top of the stack, then subtracts 1 from the stack pointer.
void CHIP8::INSTRUCT_00EE() {
    pc = stack[sp];
    sp--;
}

// Jump to location nnn.
// The interpreter sets the program counter to nnn.
void CHIP8::INSTRUCT_1nnn() {
    uint16_t cur_address = instruction & nnn;
    pc = cur_address;
}

// Call subroutine at nnn.
// The interpreter increments the stack pointer, then puts the current PC on the top of the stack. The PC is then set to nnn.
void CHIP8::INSTRUCT_2nnn() {
    uint16_t cur_address = instruction & nnn;
    sp++;
    stack[sp] = pc;
    pc = cur_address;
}

void CHIP8::INSTRUCT_3xkk() {
    // There is no uint4_t for Vx or Vy however this will suffice
    uint8_t Vx = (instruction & x) >> 8u;
    uint8_t byte = instruction & kk;
    if (registers[Vx] == byte) {
        pc += 2;
    }
}

void CHIP8::INSTRUCT_4xkk() {
    // There is no uint4_t for Vx or Vy however this will suffice
    uint8_t Vx = (instruction & x) >> 8u;
    uint8_t byte = instruction & kk;
    if (registers[Vx] != byte) {
        pc += 2;
    }
}

void CHIP8::INSTRUCT_5xy0() {
    // There is no uint4_t for Vx or Vy however this will suffice
    uint8_t Vx = (instruction & x) >> 8u;
    uint8_t Vy = (instruction & y) >> 4u;
    if (registers[Vx] == registers[Vy]) {
        pc += 2;
    }
}

void CHIP8::INSTRUCT_6xkk() {

}

int main() {
    return EXIT_SUCCESS;
}