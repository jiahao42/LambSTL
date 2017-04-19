#include "function"
#include "vector"
#include "stl_numeric.h"
#include <cassert>
#include <cstdlib>
#include <cstdio>
#include <iostream>

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

#define TEST_INT(expect,actual)	TEST_EQ_BASE((expect) == (actual),expect,actual,"%d")
#define TEST_SIZE_TYPE(expect,actual)	TEST_EQ_BASE \
((static_cast<size_t>(expect) == (actual)),static_cast<size_t>(expect),actual,"%zu")


void test_numeric() {
	/* Test accumulate */
	Vector<int> v;
	for (int i = 0; i < 10; i++) {
		v.push_back(i);
	}
	TEST_INT(45, accumulate(v.begin(), v.end(), 0));
	TEST_INT(0, accumulate(v.begin(), v.end(), 45, minus<int>()));
	TEST_INT(0, accumulate(v.begin(), v.end(), 1, multiplies<int>()));
	//TEST_INT(0, accumulate(v.begin(), v.end(), 1, divides<int>())); /* This code shall cause exception */
	
	/* Test adjacent_difference */
	adjacent_difference(v.begin(), v.end(), v.begin()); // 0, 1, 1, 1...
	TEST_INT(0, v[0]);
	for (int i = 1; i < 10; i++) {
		TEST_INT(1, v[i]);
	}
	adjacent_difference(v.begin(), v.end(), v.begin(), plus<int>()); // 0, 1, 2, 2...
	TEST_INT(0, v[0]);
	TEST_INT(1, v[1]);
	for (int i = 2; i < 10; i++) {
		TEST_INT(2, v[i]);
	}
	
}

int main(){
	test_numeric();
	printf("%d/%d (%3.2f%%) passed\n", test_pass, test_count, test_pass * 100.0 / test_count);
    return main_ret;
}











