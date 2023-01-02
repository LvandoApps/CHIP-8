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

// Skip next instruction if Vx = kk.
// The interpreter compares register Vx to kk, and if they are equal, increments the program counter by 2.
void CHIP8::INSTRUCT_3xkk() {
    // There is no uint4_t data type for Vx or Vy, however uint8_t will suffice
    uint8_t Vx = (instruction & x) >> 8u;
    uint8_t byte = instruction & kk;
    if (registers[Vx] == byte) {
        pc += 2;
    }
}

// Skip next instruction if Vx != kk.
// The interpreter compares register Vx to kk, and if they are not equal, increments the program counter by 2.
void CHIP8::INSTRUCT_4xkk() {
    uint8_t Vx = (instruction & x) >> 8u;
    uint8_t byte = instruction & kk;
    if (registers[Vx] != byte) {
        pc += 2;
    }
}

// Skip next instruction if Vx = Vy.
// The interpreter compares register Vx to register Vy, and if they are equal, increments the program counter by 2.
void CHIP8::INSTRUCT_5xy0() {
    uint8_t Vx = (instruction & x) >> 8u;
    uint8_t Vy = (instruction & y) >> 4u;
    if (registers[Vx] == registers[Vy]) {
        pc += 2;
    }
}

// Set Vx = kk.
// The interpreter puts the value kk into register Vx.
void CHIP8::INSTRUCT_6xkk() {
    uint8_t Vx = (instruction & x) >> 8u;
    uint8_t byte = instruction & kk;
    registers[Vx] = byte;
}

// Set Vx = Vx + kk.
// Adds the value kk to the value of register Vx, then stores the result in Vx.
void CHIP8::INSTRUCT_7xkk() {
    uint8_t Vx = (instruction & x) >> 8u;
    uint8_t byte = instruction & kk;
    registers[Vx] += byte;
}

// Set Vx = Vy.
// Stores the value of register Vy in register Vx.
void CHIP8::INSTRUCT_8xy0() {
    uint8_t Vx = (instruction & x) >> 8u;
    uint8_t Vy = (instruction & y) >> 4u;
    registers[Vx] = registers[Vy];
}

// Set Vx = Vx OR Vy.
// Performs a bitwise OR on the values of Vx and Vy, then stores the result in Vx. A bitwise OR compares the corrseponding bits from two values, and if either bit is 1, then the same bit in the result is also 1. Otherwise, it is 0.
void CHIP8::INSTRUCT_8xy1() {
    uint8_t Vx = (instruction & x) >> 8u;
    uint8_t Vy = (instruction & y) >> 4u;
    registers[Vx] |= registers[Vy];
}

// Set Vx = Vx AND Vy.
// Performs a bitwise AND on the values of Vx and Vy, then stores the result in Vx. A bitwise AND compares the corrseponding bits from two values, and if both bits are 1, then the same bit in the result is also 1. Otherwise, it is 0. 
void CHIP8::INSTRUCT_8xy2() {
    uint8_t Vx = (instruction & x) >> 8u;
    uint8_t Vy = (instruction & y) >> 4u;
    registers[Vx] &= registers[Vy];
}

// Set Vx = Vx XOR Vy.
// Performs a bitwise exclusive OR on the values of Vx and Vy, then stores the result in Vx. An exclusive OR compares the corrseponding bits from two values, and if the bits are not both the same, then the corresponding bit in the result is set to 1. Otherwise, it is 0. 
void CHIP8::INSTRUCT_8xy3() {
    uint8_t Vx = (instruction & x) >> 8u;
    uint8_t Vy = (instruction & y) >> 4u;
    registers[Vx] ^= registers[Vy];
}

// Set Vx = Vx + Vy, set VF = carry.
// The values of Vx and Vy are added together. If the result is greater than 8 bits (i.e., > 255,) VF is set to 1, otherwise 0. Only the lowest 8 bits of the result are kept, and stored in Vx.    
void CHIP8::INSTRUCT_8xy4() {

}

// Set Vx = Vx - Vy, set VF = NOT borrow.
// If Vx > Vy, then VF is set to 1, otherwise 0. Then Vy is subtracted from Vx, and the results stored in Vx.
void CHIP8::INSTRUCT_8xy5() {
    
}

// Set Vx = Vx SHR 1.
// If the least-significant bit of Vx is 1, then VF is set to 1, otherwise 0. Then Vx is divided by 2.
void CHIP8::INSTRUCT_8xy6() {
    
}

// Set Vx = Vy - Vx, set VF = NOT borrow.
// If Vy > Vx, then VF is set to 1, otherwise 0. Then Vx is subtracted from Vy, and the results stored in Vx.
void CHIP8::INSTRUCT_8xy7() {
    
}

// Set Vx = Vx SHL 1.
// If the most-significant bit of Vx is 1, then VF is set to 1, otherwise to 0. Then Vx is multiplied by 2.
void CHIP8::INSTRUCT_8xyE() {
    
}

// Skip next instruction if Vx != Vy.
// The values of Vx and Vy are compared, and if they are not equal, the program counter is increased by 2.
void CHIP8::INSTRUCT_9xy0() {
    
}

// Set I = nnn.
// The value of register I is set to nnn.
void CHIP8::INSTRUCT_Annn() {
    
}

// Jump to location nnn + V0.
// The program counter is set to nnn plus the value of V0.
void CHIP8::INSTRUCT_Bnnn() {
    
}

// Set Vx = random byte AND kk.
// The interpreter generates a random number from 0 to 255, which is then ANDed with the value kk. The results are stored in Vx. See instruction 8xy2 for more information on AND.
void CHIP8::INSTRUCT_Cxkk() {
    
}

// Display n-byte sprite starting at memory location I at (Vx, Vy), set VF = collision.
// The interpreter reads n bytes from memory, starting at the address stored in I. These bytes are then displayed as sprites on screen at coordinates (Vx, Vy). Sprites are XORed onto the existing screen. If this causes any pixels to be erased, VF is set to 1, otherwise it is set to 0. If the sprite is positioned so part of it is outside the coordinates of the display, it wraps around to the opposite side of the screen. See instruction 8xy3 for more information on XOR, and section 2.4, Display, for more information on the Chip-8 screen and sprites.
void CHIP8::INSTRUCT_Dxyn() {
    
}

// Skip next instruction if key with the value of Vx is pressed.
// Checks the keyboard, and if the key corresponding to the value of Vx is currently in the down position, PC is increased by 2.
void CHIP8::INSTRUCT_Ex9E() {
    
}

// Skip next instruction if key with the value of Vx is not pressed.
// Checks the keyboard, and if the key corresponding to the value of Vx is currently in the up position, PC is increased by 2.
void CHIP8::INSTRUCT_ExA1() {
    
}

// Set Vx = delay timer value.
// The value of DT is placed into Vx.
void CHIP8::INSTRUCT_Fx07() {
    
}

// Wait for a key press, store the value of the key in Vx.
// All execution stops until a key is pressed, then the value of that key is stored in Vx.
void CHIP8::INSTRUCT_Fx0A() {
    
}

// Set delay timer = Vx.
// DT is set equal to the value of Vx.
void CHIP8::INSTRUCT_Fx15() {
    
}

// Set sound timer = Vx.
// ST is set equal to the value of Vx.
void CHIP8::INSTRUCT_Fx18() {
    
}

// Set I = I + Vx.
// The values of I and Vx are added, and the results are stored in I.
void CHIP8::INSTRUCT_Fx1E() {
    
}

// Set I = location of sprite for digit Vx.
// The value of I is set to the location for the hexadecimal sprite corresponding to the value of Vx. See section 2.4, Display, for more information on the Chip-8 hexadecimal font.
void CHIP8::INSTRUCT_Fx29() {
    
}

// Store BCD representation of Vx in memory locations I, I+1, and I+2.
// The interpreter takes the decimal value of Vx, and places the hundreds digit in memory at location in I, the tens digit at location I+1, and the ones digit at location I+2.
void CHIP8::INSTRUCT_Fx33() {
    
}

// Store registers V0 through Vx in memory starting at location I.
// The interpreter copies the values of registers V0 through Vx into memory, starting at the address in I.
void CHIP8::INSTRUCT_Fx55() {
    
}

// Read registers V0 through Vx from memory starting at location I.
// The interpreter reads values from memory starting at location I into registers V0 through Vx.
void CHIP8::INSTRUCT_Fx65() {
    
}

int main() {
    return EXIT_SUCCESS;
}