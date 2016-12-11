main: vector.o test.o
	g++ -g -o main vector.o test.o

test.o:test.cpp vector.h
	g++ -g -c test.cpp

vector.o:vector.h vector.cpp
	g++ -g -c vector.cpp

clean:
	rm *.o
