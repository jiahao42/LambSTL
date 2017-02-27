#include "function"
#include "vector"
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

template<class T>
void vector_init(Vector<T>& v1, Vector<T>& v2) {
	v1.clear();
	v2.clear();
	for (int i = 0; i < 5; i++) {
		v1.push_back(i);
		v2.push_back(i + 1);
	}
}

template <class T, class BinaryOperation>
Vector<T> test_arithmetic_aux(Vector<T>& v1, Vector<T> v2, BinaryOperation f) {
	assert(v1.size() == v2.size());
	Vector<T> tmp;
	for (int i = 0; i < v1.size(); i++) {
		tmp.push_back(f(v1[i], v2[i]));
	}
	return tmp;
}


void test_arithmetic() {
	for (int i = 0; i < 10; i++) {
		TEST_INT(10, (plus<int>()(i, 10 - i)));
	}
	Vector<int> v1, v2;
	
	vector_init(v1, v2);
	Vector<int> res = test_arithmetic_aux(v1, v2, multiplies<int>());
	for (int i = 0; i < 5; i++) {
		
		TEST_INT(i * (i + 1), res[i]);
	}
	
	vector_init(v1, v2);
	res = test_arithmetic_aux(v1, v2, plus<int>());
	for (int i = 0; i < 5; i++) {
		TEST_INT(i + i + 1, res[i]);
	}
}

void test_relation() {
	TEST_INT(1, less<int>()(1, 2));
	TEST_INT(0, less<int>()(2, 1));
	TEST_INT(1, greater<int>()(2, 1));
	TEST_INT(0, greater<int>()(1, 2));
	TEST_INT(1, equal_to<int>()(3, 3));
	TEST_INT(0, equal_to<int>()(2, 3));
	TEST_INT(1, not_equal_to<int>()(2, 3));
	TEST_INT(0, not_equal_to<int>()(2, 2));
	TEST_INT(1, greater_equal<int>()(3, 3));
	TEST_INT(0, greater_equal<int>()(2, 3));
	TEST_INT(1, less_equal<int>()(2, 3));
	TEST_INT(0, less_equal<int>()(3, 2));
}

void test_logical() {
	TEST_INT(1, logical_and<int>()(1, 1));
	TEST_INT(0, logical_and<int>()(1, 0));
	TEST_INT(1, logical_or<int>()(1, 1));
	TEST_INT(0, logical_or<int>()(0, 0));
	TEST_INT(1, logical_not<int>()(0));
	TEST_INT(0, logical_not<int>()(1));
}


int main(){
	test_arithmetic();
	test_relation();
	test_logical();
	printf("%d/%d (%3.2f%%) passed\n", test_pass, test_count, test_pass * 100.0 / test_count);
    return main_ret;
}











