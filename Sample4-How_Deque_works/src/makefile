objects = test.o deque.o
res = test.cpp deque.h
CXX=g++
CXXFLAGS= -g -O3 -std=c++11
program=test

test: $(objects)
	$(CXX) $(CXXFLAGS) -o $(program) $(objects)

test.o : test.cpp

deque.o : deque.cpp deque.h

clean:
	rm $(objects)
