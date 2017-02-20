objects = test.o
CXX = g++
RES = test.cpp
DEPS = list.h
INC = ./include/
CXXFLAGS = -g -O3 -std=c++11 -I$(INC)
program=test

test: $(objects)
	$(CXX) $(CXXFLAGS) -o $(program) $(objects)


clean:
	rm $(objects)
