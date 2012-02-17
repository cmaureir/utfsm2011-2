CXX = g++
CXXFLAGS = -Wall -lboost_program_options

BIN =  utils sp

all: $(BIN)

utils: utils.cpp utils.hpp
	g++ -c utils.cpp $(CXXFLAGS)

main.o: main.cpp

sp: main.o
	$(CXX) $^ -o $@ $(CXXFLAGS)

clean:
	@rm -vf *.o $(BIN)

.PHONY: all clean
