OBJS := src/main.o src/drawscreen.o src/chip8.o 

CXXFLAGS := -I src/include
CXX = g++
LDFLAGS := -L src/lib -lSDL2main -lSDL2 $(shell pkg-config --cflags --libs sdl2)

emulator: $(OBJS)
	g++ $(LDFLAGS) -o emulator $(OBJS)

clean:
	rm -f src/*.o
	rm -f emulator

all: emulator
