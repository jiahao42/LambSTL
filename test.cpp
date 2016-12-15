#include "vector.h"
#include <cstdlib>
#include <cstdio>

using namespace std;

int test_count = 0;
int test_pass = 0;
int main_ret = 0;
#define TEST_EQ_BASE(equality,expect,actual,format)	\
	do {	\
		test_count++;	\
		if (equality){	\
			test_pass++;\
		}else{	\
			main_ret = 1;	\
			fprintf(stderr,"%s:%d: expect: " format " actual: " format "\n",__FILE__,__LINE__,expect,actual);\
		}	\
	}while (0)

#define TEST_NUMBER(expect,actual)	TEST_EQ_BASE((expect) == (actual),expect,actual,"%d")

void test_vector(){
	Vector<int> v2;
	TEST_NUMBER(0,v2.capacity());
	v2.push_back(1);
	TEST_NUMBER(1,v2.size());
	TEST_NUMBER(1,v2.capacity());
	TEST_NUMBER(1,*v2.begin());
	TEST_NUMBER(1,v2[0]);
	v2.push_back(2);
	TEST_NUMBER(2,v2[1]);
	TEST_NUMBER(2,v2.capacity());
	TEST_NUMBER(2,v2.size());
	v2.push_back(3);
	v2.push_back(4);
	v2.push_back(5);
	TEST_NUMBER(8,v2.capacity());
	TEST_NUMBER(5,v2.size());
}


int main(){
	test_vector();
	printf("%d/%d (%3.2f%%) passed\n", test_pass, test_count, test_pass * 100.0 / test_count);
    return main_ret;
}

