objects = test.o stack.o queue.o slist.o
res = test.cpp stack.h queue.h slist.h
CXX=g++
CXXFLAGS= -g -O3 -std=c++11
program=test

test: $(objects)
	$(CXX) $(CXXFLAGS) -o $(program) $(objects)

test.o : test.cpp

stack.o : stack.cpp stack.h

queue.o : queue.cpp queue.h

slist.o : slist.cpp slist.h
clean:
	rm $(objects)
