objects = test.o stack.o queue.o
res = test.cpp stack.h queue.h
CXX=g++
CXXFLAGS= -g -O3 -std=c++11
program=test

test: $(objects)
	$(CXX) $(CXXFLAGS) -o $(program) $(objects)

test.o : test.cpp

stack.o : stack.cpp stack.h

queue.o : queue.cpp queue.h
clean:
	rm $(objects)
