objects = list.o slist.o test.o
res = test.cpp list.h slist.h
CXX=g++
CXXFLAGS= -g -O3 -std=c++11
program=test

test: $(objects)
	$(CXX) $(CXXFLAGS) -o $(program) $(objects)

test.o : test.cpp

list.o : list.cpp list.h

slist.o : slist.cpp slist.h

clean:
	rm $(objects)
