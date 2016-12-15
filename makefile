objects = vector.o vector_test.o
CXX=g++
CXXFLAGS= -g -O3
program=test

test: $(objects)
	$(CXX) $(CXXFLAGS) -o $(program) $(objects)

vector_test.o:vector_test.cpp vector.h
	$(CXX) $(CXXFLAGS) -c vector_test.cpp

vector.o:vector.h vector.cpp
	$(CXX) $(CXXFLAGS) -c vector.cpp

clean:
	rm $(objects)
