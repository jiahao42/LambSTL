objects = test.o
CXX = g++
RES = test.cpp
INC = ../include/
CXXFLAGS = -g -Wall -O3 -std=c++11 -I$(INC)
program=test

test: $(objects)
	$(CXX) $(CXXFLAGS) -o $(program) $(objects)


clean:
	rm $(objects)
