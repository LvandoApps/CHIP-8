#include <stdint.h>

const unsigned int KEY_COUNT = 16;
const unsigned int MEMORY_SIZE = 4096;
const unsigned int REGISTER_COUNT = 16;
const unsigned int STACK_LEVELS = 16;
const unsigned int VIDEO_HEIGHT = 32;
const unsigned int VIDEO_WIDTH = 64;

class CHIP8 {
    public:
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
};