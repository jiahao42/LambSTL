test: vector.o vector_test.o
	g++ -g -o test vector.o vector_test.o

vector_test.o:vector_test.cpp vector.h
	g++ -g -c vector_test.cpp

vector.o:vector.h vector.cpp
	g++ -g -c vector.cpp

clean:
	rm *.o
