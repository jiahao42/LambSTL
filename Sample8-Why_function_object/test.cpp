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
template <class T>
Vector<T> test_arithmetic_aux(Vector<T>& v1, Vector<T> v2, multiplies<T> f) {
	assert(v1.size() == v2.size());
	Vector<T> tmp;
	for (int i = 0; i < v1.size(); i++) {
		tmp.push_back(f(v1[i], v2[i]));
	}
	return tmp;
}

template <class T>
Vector<T> test_arithmetic_aux(Vector<T>& v1, Vector<T>& v2, plus<T> f) {
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



int main(){
	test_arithmetic();
	printf("%d/%d (%3.2f%%) passed\n", test_pass, test_count, test_pass * 100.0 / test_count);
    return main_ret;
}











