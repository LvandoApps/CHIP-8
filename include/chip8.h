#include <stdint.h>

// Some const's to prevent magic numbers
const unsigned int KEY_COUNT = 16;
const unsigned int RAM_SIZE = 4096;
const unsigned int REGISTER_COUNT = 16;
const unsigned int STACK_LEVELS = 16;
const unsigned int DISPLAY_HEIGHT = 32;
const unsigned int DISPLAY_WIDTH = 64;
const unsigned int START_ADDRESS = 0x200;
const unsigned int SPRITE_SIZE = 80;
const unsigned int SPRITE_START_ADDRESS = 0x50;

class CHIP8 {
    public:
        // Bool for debug
        bool debug_option;
        // All the required components for the CHIP8
        uint16_t registers[REGISTER_COUNT];
        uint8_t ram[RAM_SIZE];
        uint16_t index;
        uint16_t pc;
        uint16_t stack[STACK_LEVELS];
        uint8_t dt;
        uint8_t st;
        uint32_t display[DISPLAY_WIDTH * DISPLAY_HEIGHT] = {0};
        uint8_t keypad[KEY_COUNT];
        uint8_t sp;
        uint16_t instruction;
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
        uint8_t sprite[SPRITE_SIZE] =
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
        //  nnn or addr - A 12-bit value, the lowest 12 bits of the instruction
        //  n or nibble - A 4-bit value, the lowest 4 bits of the instruction
        //  x - A 4-bit value, the lower 4 bits of the high byte of the instruction
        //  y - A 4-bit value, the upper 4 bits of the low byte of the instruction
        //  kk or byte - An 8-bit value, the lowest 8 bits of the instruction
        unsigned int nnn = 0x0FFF;
        unsigned int n = 0x000F;
        // Reminder that for x, it is the lower 4 bits of the high byte (so bits 8-12), so shift accordingly when using (8).
        // Reminder that for y, it is the upper 4 bits of the low byte (so bits 4-7), so shift accordingly when using (4).
        unsigned int x = 0x0F00;
        unsigned int y = 0x00F0;
        unsigned int kk = 0x00FF;

    public:
        CHIP8();
        void LoadGame(char const* filename, bool& check_validity);
        void InstructionSequence();
    
    private:
        // All instructions for the CHIP8 below:
        void INSTRUCT_0nnn();
        void INSTRUCT_00E0();
        void INSTRUCT_00EE();
        void INSTRUCT_1nnn();
        void INSTRUCT_2nnn();
        void INSTRUCT_3xkk();
        void INSTRUCT_4xkk();
        void INSTRUCT_5xy0();
        void INSTRUCT_6xkk();
        void INSTRUCT_7xkk();
        void INSTRUCT_8xy0();
        void INSTRUCT_8xy1();
        void INSTRUCT_8xy2();
        void INSTRUCT_8xy3();
        void INSTRUCT_8xy4();
        void INSTRUCT_8xy5();
        void INSTRUCT_8xy6();
        void INSTRUCT_8xy7();
        void INSTRUCT_8xyE();
        void INSTRUCT_9xy0();
        void INSTRUCT_Annn();
        void INSTRUCT_Bnnn();
        void INSTRUCT_Cxkk();
        void INSTRUCT_Dxyn();
        void INSTRUCT_Ex9E();
        void INSTRUCT_ExA1();
        void INSTRUCT_Fx07();
        void INSTRUCT_Fx0A();
        void INSTRUCT_Fx15();
        void INSTRUCT_Fx18();
        void INSTRUCT_Fx1E();
        void INSTRUCT_Fx29();
        void INSTRUCT_Fx33();
        void INSTRUCT_Fx55();
        void INSTRUCT_Fx65();
};