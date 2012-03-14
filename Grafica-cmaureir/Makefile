CXXFLAGS = -Wall -lglut -lGLU -lGL -lstdc++ -pedantic -DGL_GLEXT_PROTOTYPES -lm
all: bodies

Bitmap.o: Bitmap.cpp Bitmap.h
core.o: core.cpp core.hpp
bodies: Bitmap.o core.o
clean:
	@rm -vf *.o bodies
.PHONY: all clean
