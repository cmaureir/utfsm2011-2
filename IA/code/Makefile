CXX = g++
CXXFLAGS = -Wall
LDFLAGS = -lboost_program_options
BIN =  utils.o scattersearch.o sp

all: $(BIN)
utils.o: utils.cpp utils.hpp
scattersearch.o: scattersearch.cpp scattersearch.hpp
main.o: main.cpp

sp: main.o utils.o scattersearch.o  
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@ 

clean:
	@rm -vf *.o $(BIN)

.PHONY: all clean
