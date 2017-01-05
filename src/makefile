objects = vector.o list.o test.o deque.o
res = test.cpp vector.h list.h deque.h
CXX=g++
CXXFLAGS= -g -O3 -std=c++11
program=test

test: $(objects)
	$(CXX) $(CXXFLAGS) -o $(program) $(objects)

test.o : test.cpp

list.o : list.cpp list.h

vector.o : vector.cpp vector.h

deque.o : deque.cpp deque.h

clean:
	rm $(objects)
