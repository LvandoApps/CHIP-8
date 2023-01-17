#include <string.h>
#include <iostream>
#include <fstream>
#include <random>
#include "../include/chip8.h"

CHIP8::CHIP8() {
    pc = START_ADDRESS;
    // Load the fonts 0 through F into the memory of the CHIP8, starting at 0x050 and ending at 0x0A0 (80 bytes)
    for (unsigned int i = 0; i < SPRITE_SIZE; i++) {
        ram[SPRITE_START_ADDRESS + i] = sprite[i];
    }
}

void CHIP8::LoadGame(char const* filename, bool& check_validity) {
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
            ram[START_ADDRESS + i] = contents[i];
        }
        delete[] contents;
    }
    else {
        check_validity = false;
    }
}

void CHIP8::InstructionSequence() {
    // Fetch the instruction from the loaded rom/game first
    instruction = (ram[pc] << 8u) | (ram[pc + 1]);
    // We will have to either increment pc before each instruction or after each instruction, here makes more sense than including it at the end of every instruction
    pc += 2;
    // A big switch statement that handles all the instructions decoding/executing, I'm sure there are better ways to do this but this is the easiest to me at the moment
    // Add some more debugging options here later if needed
    switch(instruction & 0xF000) {
        case 0x0000:
            switch(instruction & 0x00FF) {
                case 0x00E0:
                    INSTRUCT_00E0();
                    break;

                case 0x00EE:
                    INSTRUCT_00EE();
                    break;
                
                default:
                    printf("ERROR: Instruction unrecognized with value 0x%X\n", instruction);
                    exit(EXIT_FAILURE);
            }
            break;

        case 0x1000:
            INSTRUCT_1nnn();
            break;

        case 0x2000:
            INSTRUCT_2nnn();
            break;

        case 0x3000:
            INSTRUCT_3xkk();
            break;

        case 0x4000:
            INSTRUCT_4xkk();
            break;

        case 0x5000:
            INSTRUCT_5xy0();
            break;

        case 0x6000:
            INSTRUCT_6xkk();
            break;

        case 0x7000:
            INSTRUCT_7xkk();
            break;

        case 0x8000:
            switch(instruction & 0x000F) {
                case 0x0000:
                    INSTRUCT_8xy0();
                    break;

                case 0x0001:
                    INSTRUCT_8xy1();
                    break;

                case 0x0002:
                    INSTRUCT_8xy2();
                    break;

                case 0x0003:
                    INSTRUCT_8xy3();
                    break;

                case 0x0004:
                    INSTRUCT_8xy4();
                    break;

                case 0x0005:
                    INSTRUCT_8xy5();
                    break;
                
                case 0x0006:
                    INSTRUCT_8xy6();
                    break;

                case 0x0007:
                    INSTRUCT_8xy7();
                    break;

                case 0x000E:
                    INSTRUCT_8xyE();
                    break;
                
                default:
                    printf("ERROR: Instruction unrecognized with value 0x%X\n", instruction);
                    exit(EXIT_FAILURE);
            }
            break;
        
        case 0x9000:
            INSTRUCT_9xy0();
            break;
        
        case 0xA000:
            INSTRUCT_Annn();
            break;
        
        case 0xB000:
            INSTRUCT_Bnnn();
            break;

        case 0xC000:
            INSTRUCT_Cxkk();
            break;

        case 0xD000:
            INSTRUCT_Dxyn();
            break;
            
        case 0xE000:
            switch(instruction & 0x00FF) {
                case 0x009E:
                    INSTRUCT_Ex9E();
                    break;

                case 0x00A1:
                    INSTRUCT_ExA1();
                    break;

                default:
                    printf("ERROR: Instruction unrecognized with value 0x%X\n", instruction);
                    exit(EXIT_FAILURE);
            }
            break;
        
        case 0xF000:
            switch(instruction & 0x00FF) {
                case 0x0007:
                    INSTRUCT_Fx07();
                    break;

                case 0x000A:
                    INSTRUCT_Fx0A();
                    break;

                case 0x0015:
                    INSTRUCT_Fx15();
                    break;

                case 0x0018:
                    INSTRUCT_Fx18();
                    break;

                case 0x001E:
                    INSTRUCT_Fx1E();
                    break;

                case 0x0029:
                    INSTRUCT_Fx29();
                    break;

                case 0x0033:
                    INSTRUCT_Fx33();
                    break;

                case 0x0055:
                    INSTRUCT_Fx55();
                    break;

                case 0x065:
                    INSTRUCT_Fx65();
                    break;

                default:
                    printf("ERROR: Instruction unrecognized with value 0x%X\n", instruction);
                    exit(EXIT_FAILURE);
            }
            break;
        
        default:
            printf("ERROR: Instruction unrecognized with value 0x%X\n", instruction);
            exit(EXIT_FAILURE);
    }

    // Finally we decrement the delay timer and/or the sound timer should they be set
    if (dt > 0) {
        --dt;
    }

    if (st > 0) {
        --st;
    }
}

// Clear the display.
void CHIP8::INSTRUCT_00E0() {
    memset(display, 0, sizeof(display));
}

// Return from a subroutine.
// The interpreter sets the program counter to the address at the top of the stack, then subtracts 1 from the stack pointer.
void CHIP8::INSTRUCT_00EE() {
    sp--;
    pc = stack[sp];
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
    stack[sp] = pc;
    sp++;
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
    uint8_t Vx = (instruction & x) >> 8u;
    uint8_t Vy = (instruction & y) >> 4u;
    if (registers[Vx] + registers[Vy] > 255u) {
        registers[0xF] = 1;
    }
    else {
        registers[0xF] = 0;
    }
    registers[Vx] = (registers[Vx] + registers[Vy]) & kk;
}

// Set Vx = Vx - Vy, set VF = NOT borrow.
// If Vx > Vy, then VF is set to 1, otherwise 0. Then Vy is subtracted from Vx, and the results stored in Vx.
void CHIP8::INSTRUCT_8xy5() {
    uint8_t Vx = (instruction & x) >> 8u;
    uint8_t Vy = (instruction & y) >> 4u;
    if (registers[Vx] > registers[Vy]) {
        registers[0xF] = 1;
    }
    else {
        registers[0xF] = 0;
    }
    registers[Vx] -= registers[Vy];
}

// Set Vx = Vx SHR 1.
// If the least-significant bit of Vx is 1, then VF is set to 1, otherwise 0. Then Vx is divided by 2.
void CHIP8::INSTRUCT_8xy6() {
    uint8_t Vx = (instruction & x) >> 8u;
    if ((registers[Vx] & 1u) == 1) {
        registers[0xF] = 1;
    }
    else {
        registers[0xF] = 0;
    }
    registers[Vx] >>= 1;
}

// Set Vx = Vy - Vx, set VF = NOT borrow.
// If Vy > Vx, then VF is set to 1, otherwise 0. Then Vx is subtracted from Vy, and the results stored in Vx.
void CHIP8::INSTRUCT_8xy7() {
    uint8_t Vx = (instruction & x) >> 8u;
    uint8_t Vy = (instruction & y) >> 4u;
    if (registers[Vy] > registers[Vx]) {
        registers[0xF] = 1;
    }
    else {
        registers[0xF] = 0;
    }
    registers[Vx] = registers[Vy] - registers[Vx];
}

// Set Vx = Vx SHL 1.
// If the most-significant bit of Vx is 1, then VF is set to 1, otherwise to 0. Then Vx is multiplied by 2.
void CHIP8::INSTRUCT_8xyE() {
    uint8_t Vx = (instruction & x) >> 8u;
    if ((registers[Vx] & 128u) == 1) {
        registers[0xF] = 1;
    }
    else {
        registers[0xF] = 0;
    }
    registers[Vx] <<= 1;
}

// Skip next instruction if Vx != Vy.
// The values of Vx and Vy are compared, and if they are not equal, the program counter is increased by 2.
void CHIP8::INSTRUCT_9xy0() {
    uint8_t Vx = (instruction & x) >> 8u;
    uint8_t Vy = (instruction & y) >> 4u;
    if (registers[Vx] != registers[Vy]) {
        pc += 2;
    }
}

// Set I = nnn.
// The value of register I is set to nnn.
void CHIP8::INSTRUCT_Annn() {
    uint16_t cur_address = instruction & nnn;
    index = cur_address;
}

// Jump to location nnn + V0.
// The program counter is set to nnn plus the value of V0.
void CHIP8::INSTRUCT_Bnnn() {
    uint16_t cur_address = instruction & nnn;
    pc = cur_address + registers[0x0];
}

// Set Vx = random byte AND kk.
// The interpreter generates a random number from 0 to 255, which is then ANDed with the value kk. The results are stored in Vx. See instruction 8xy2 for more information on AND.
void CHIP8::INSTRUCT_Cxkk() {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(0,255); // distribution in range [0, 255]
    uint8_t Vx = (instruction & x) >> 8u;
    uint8_t byte = instruction & kk;
    registers[Vx] = byte & dist6(rng);
    
}

// Display n-byte sprite starting at memory location I at (Vx, Vy), set VF = collision.
// The interpreter reads n bytes from memory, starting at the address stored in I. These bytes are then displayed as sprites on screen at coordinates (Vx, Vy). Sprites are XORed onto the existing screen. If this causes any pixels to be erased, VF is set to 1, otherwise it is set to 0. If the sprite is positioned so part of it is outside the coordinates of the display, it wraps around to the opposite side of the screen. See instruction 8xy3 for more information on XOR, and section 2.4, Display, for more information on the Chip-8 screen and sprites.
void CHIP8::INSTRUCT_Dxyn() {
    uint8_t Vx = (instruction & x) >> 8u;
    uint8_t Vy = (instruction & y) >> 4u;
    uint8_t sprite_height = instruction & n;

    // This will ensure textures are wrapped back onto the screen should they go outside the bounds (i.e reset to 0 when reaching the maximum)
    uint8_t cur_x = registers[Vx] % DISPLAY_WIDTH;
    uint8_t cur_y = registers[Vy] % DISPLAY_HEIGHT;

    // Reset collision register to 0
    registers[0xF] = 0;

    // The loop that continues to draw sprites onto the screen, works in tangent with SDL functions to continuously update textures and allow the game to be displayed correctly
    for (uint8_t y_coord = 0; y_coord < sprite_height; y_coord++) {
        uint8_t pixel_on_sprite = ram[index + y_coord];
        for (uint8_t x_coord = 0; x_coord < 8; x_coord++) {
            uint32_t* pixel_on_screen = &display[(cur_y + y_coord) * DISPLAY_WIDTH + (cur_x + x_coord)];
            if ((pixel_on_sprite & (0x80 >> x_coord))) {
                // If the sprite pixel is on at the same time the screen pixel is on, then there is a collision
                if (*pixel_on_screen == 0xFFFFFFFF) {
                    registers[0xF] = 1;
                }
                // We then XOR the sprite pixel onto the screen as requested
                *pixel_on_screen ^= 0xFFFFFFFF;
            }
        }
    }
}

// Skip next instruction if key with the value of Vx is pressed.
// Checks the keyboard, and if the key corresponding to the value of Vx is currently in the down position, PC is increased by 2.
void CHIP8::INSTRUCT_Ex9E() {
    uint8_t Vx = (instruction & x) >> 8u;
    uint8_t key_Vx = registers[Vx];
    if (keypad[key_Vx]) {
        pc += 2;
    }
}

// Skip next instruction if key with the value of Vx is not pressed.
// Checks the keyboard, and if the key corresponding to the value of Vx is currently in the up position, PC is increased by 2.
void CHIP8::INSTRUCT_ExA1() {
    uint8_t Vx = (instruction & x) >> 8u;
    uint8_t key_Vx = registers[Vx];
    if (!keypad[key_Vx]) {
        pc += 2;
    }
}

// Set Vx = delay timer value.
// The value of DT is placed into Vx.
void CHIP8::INSTRUCT_Fx07() {
    uint8_t Vx = (instruction & x) >> 8u;
    registers[Vx] = dt;
}

// Wait for a key press, store the value of the key in Vx.
// All execution stops until a key is pressed, then the value of that key is stored in Vx.
void CHIP8::INSTRUCT_Fx0A() {
    uint8_t Vx = (instruction & x) >> 8u;
    if (keypad[0]) {
		registers[Vx] = 0;
	}
	else if (keypad[1]) {
		registers[Vx] = 1;
	}
	else if (keypad[2]) {
		registers[Vx] = 2;
	}
	else if (keypad[3]) {
		registers[Vx] = 3;
	}
	else if (keypad[4]) {
		registers[Vx] = 4;
	}
	else if (keypad[5]) {
		registers[Vx] = 5;
	}
	else if (keypad[6]) {
		registers[Vx] = 6;
	}
	else if (keypad[7]) {
		registers[Vx] = 7;
	}
	else if (keypad[8]) {
		registers[Vx] = 8;
	}
	else if (keypad[9]) {
		registers[Vx] = 9;
	}
	else if (keypad[10]) {
		registers[Vx] = 10;
	}
	else if (keypad[11]) {
		registers[Vx] = 11;
	}
	else if (keypad[12]) {
		registers[Vx] = 12;
	}
	else if (keypad[13]) {
		registers[Vx] = 13;
	}
	else if (keypad[14]) {
		registers[Vx] = 14;
	}
	else if (keypad[15]) {
		registers[Vx] = 15;
	}
    // If we decrement the pc by 2 then we are effectively looping this instruction, hence waiting
	else {
		pc -= 2;
	}

}

// Set delay timer = Vx.
// DT is set equal to the value of Vx.
void CHIP8::INSTRUCT_Fx15() {
    uint8_t Vx = (instruction & x) >> 8u;
    dt = registers[Vx];
}

// Set sound timer = Vx.
// ST is set equal to the value of Vx.
void CHIP8::INSTRUCT_Fx18() {
    uint8_t Vx = (instruction & x) >> 8u;
    st = registers[Vx];
}

// Set I = I + Vx.
// The values of I and Vx are added, and the results are stored in I.
void CHIP8::INSTRUCT_Fx1E() {
    uint8_t Vx = (instruction & x) >> 8u;
    index += registers[Vx];
}

// Set I = location of sprite for digit Vx.
// The value of I is set to the location for the hexadecimal sprite corresponding to the value of Vx. See section 2.4, Display, for more information on the Chip-8 hexadecimal font.
void CHIP8::INSTRUCT_Fx29() {
    uint8_t Vx = (instruction & x) >> 8u;
    // Sprites are 5 bytes long and will always start at the sprite start address (0x50), as such the start of any given sprite will be an increment of 5
    index = SPRITE_START_ADDRESS + (5 * registers[Vx]);
}

// Store BCD representation of Vx in memory locations I, I+1, and I+2.
// The interpreter takes the decimal value of Vx, and places the hundreds digit in memory at location in I, the tens digit at location I+1, and the ones digit at location I+2.
void CHIP8::INSTRUCT_Fx33() {
    uint8_t Vx = (instruction & x) >> 8u;
    ram[index] = Vx / 100;
    ram[index + 1] = (Vx / 10) % 10;
    ram[index + 2] = Vx % 10;
}

// Store registers V0 through Vx in memory starting at location I.
// The interpreter copies the values of registers V0 through Vx into memory, starting at the address in I.
void CHIP8::INSTRUCT_Fx55() {
    uint8_t Vx = (instruction & x) >> 8u;
    for (uint8_t i = 0; i < Vx; i++) {
        ram[index + i] = registers[i];
    }
}

// Read registers V0 through Vx from memory starting at location I.
// The interpreter reads values from memory starting at location I into registers V0 through Vx.
void CHIP8::INSTRUCT_Fx65() {
    uint8_t Vx = (instruction & x) >> 8u;
    for (uint8_t i = 0; i < Vx; i++) {
        registers[i] = ram[index + i];
    }
}