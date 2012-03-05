CXX = g++
CXXFLAGS = -Wall
LDFLAGS =-lglut -lGLU -lGL -lstdc++
BIN = bodies

all=$(BIN)

all:
	g++ -c extra.cpp
	g++ bodies.cpp extra.o -o bodies $(CXXFLAGS) $(LDFLAGS)

clean:
	@rm -vf *.o $(BIN)

.PHONY: all clean
