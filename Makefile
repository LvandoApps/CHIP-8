all:
	g++ -I src/include -L src/lib -o emulator src/main.cpp src/drawscreen.cpp src/chip8.cpp -lmingw32 -lSDL2main -lSDL2