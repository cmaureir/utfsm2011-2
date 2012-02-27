CXX = g++
CXXFLAGS = -Wall
LDFLAGS = -lboost_program_options
BIN =  scattersearch.o sp

#all: $(BIN)
#scattersearch.o: scattersearch.cpp 
#main.o: main.cpp
#sp: main.o scattersearch.o  
#	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@ 

all:
	g++ -c scattersearch.cpp
	g++ main.cpp scattersearch.o -o sp $(CXXFLAGS) $(LDFLAGS)

clean:
	@rm -vf *.o $(BIN)

.PHONY: all clean
