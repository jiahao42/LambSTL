objects = test.o stack.o
res = test.cpp stack.h
CXX=g++
CXXFLAGS= -g -O3 -std=c++11
program=test

test: $(objects)
	$(CXX) $(CXXFLAGS) -o $(program) $(objects)

test.o : test.cpp

stack.o : stack.cpp stack.h

clean:
	rm $(objects)
