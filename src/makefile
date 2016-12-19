#objects = vector.o list.o test.o
res = test.cpp vector.h list.h
CXX=g++
CXXFLAGS= -g -O3 -std=c++11
program=test

test: $(objects)
	$(CXX) $(CXXFLAGS) $(res) -o $(program) 

clean:
	rm $(program)
