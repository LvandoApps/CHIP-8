OBJS := src/main.o src/drawscreen.o src/chip8.o 

CXXFLAGS := -I src/include
CXX = g++
LDFLAGS := -lSDL2main -lSDL2

emulator: $(OBJS)
	g++ $(LDFLAGS) -o emulator $(OBJS)

all: emulator
