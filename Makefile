OBJS := src/main.o src/drawscreen.o src/chip8.o 

CXXFLAGS := -I src/include
CXX = g++
LDFLAGS := $(shell pkg-config --cflags --libs sdl2)

emulator: $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS)

clean:
	rm -f src/*.o
	rm -f emulator

all: emulator
