objects = vector.o list.o test.o
CXX=g++
CXXFLAGS= -g -O3 -std=c++11
program=test

test: $(objects)
	$(CXX) $(CXXFLAGS) -o $(program) $(objects)

test.o:test.cpp vector.h list.h

vector.o:vector.h vector.cpp

list.o:list.h list.cpp

clean:
	rm $(objects)
