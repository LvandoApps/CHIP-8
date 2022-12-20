#include <stdint.h>

const unsigned int KEY_COUNT = 16;
const unsigned int MEMORY_SIZE = 4096;
const unsigned int REGISTER_COUNT = 16;
const unsigned int STACK_LEVELS = 16;
const unsigned int VIDEO_HEIGHT = 32;
const unsigned int VIDEO_WIDTH = 64;
const unsigned int START_ADDRESS = 0x200;
const unsigned int FONTSET_SIZE = 80;
const unsigned int FONTSET_START_ADDRESS = 0x50;

class CHIP8 {
    public:
        // All the required components for the CHIP8
        uint16_t registers[REGISTER_COUNT];
        uint8_t memory[MEMORY_SIZE];
        uint16_t index;
        uint16_t pc;
        uint16_t stack[STACK_LEVELS];
        uint8_t delayTimer;
        uint8_t soundTimer;
        uint32_t display[VIDEO_WIDTH * VIDEO_HEIGHT];
        uint8_t keypad[KEY_COUNT];
        uint8_t sp;
        // The CHIP8 has a built-in font with sprite data representing the hexadecimal numbers from 0 through F and should be 4 pixels 
        // wide and 5 pixels tall (where in this case, pixel = bit, i.e black and white when displayed). 
        // As such each character has a size of 5 bytes, and when laid out vertically in binary notation should resemble the shape of the given character. 
        // For example, the character 0 is defined by 0xF0, 0x90, 0x90, 0x90, 0xF0, which is converted to binary notation
        // and laid vertically to resemble the shape of the character 0 with a width of 4 pixels and height of 5 pixels (seen below)
        // 11110000
        // 10010000
        // 10010000
        // 10010000
        // 11110000
        uint8_t fontset[FONTSET_SIZE] =
        {
            0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
            0x20, 0x60, 0x20, 0x20, 0x70, // 1
            0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
            0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
            0x90, 0x90, 0xF0, 0x10, 0x10, // 4
            0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
            0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
            0xF0, 0x10, 0x20, 0x40, 0x40, // 7
            0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
            0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
            0xF0, 0x90, 0xF0, 0x90, 0x90, // A
            0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
            0xF0, 0x80, 0x80, 0x80, 0xF0, // C
            0xE0, 0x90, 0x90, 0x90, 0xE0, // D
            0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
            0xF0, 0x80, 0xF0, 0x80, 0x80  // F
        };

    public:
        CHIP8();
        ~CHIP8();
        void loadGame(char const* filename);

};