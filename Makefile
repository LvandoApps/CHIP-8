all:
	g++ -W -Wall -Werror -I src/include -L src/lib -o emulator src/main.cpp src/drawscreen.cpp src/chip8.cpp -lSDL2.dll