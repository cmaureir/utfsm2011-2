CXX = g++
CXXFLAGS = -Wall -lboost_program_options

BIN =  utils scattersearch sp

all: $(BIN)

utils: utils.cpp utils.hpp
	g++ -c utils.cpp $(CXXFLAGS)

scattersearch: scattersearch.cpp scattersearch.hpp
	g++ -c scattersearch.cpp $(CXXFLAGS)

main.o: main.cpp

sp: main.o
	$(CXX) $^ -o $@ $(CXXFLAGS)

clean:
	@rm -vf *.o $(BIN)

.PHONY: all clean
