CXX = g++
CXXFLAGS = -Wall
LDFLAGS =-lglut -lGLU -lGL -lstdc++ -pedantic -DGL_GLEXT_PROTOTYPES -lm 
BIN = bodies

all=$(BIN)

all:
	g++ -c Bitmap.cpp
	g++ -c extra.cpp $(CXXFLAGS) $(LDFLAGS)
	g++ bodies.cpp extra.o Bitmap.o -o bodies $(CXXFLAGS) $(LDFLAGS)

clean:
	@rm -vf *.o $(BIN)

.PHONY: all clean
