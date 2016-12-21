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

#define TEST_INT(expect,actual)	TEST_EQ_BASE((expect) == (actual),expect,actual,"%d")
#define TEST_SIZE_TYPE(expect,actual)	TEST_EQ_BASE \
((static_cast<size_t>(expect) == (actual)),static_cast<size_t>(expect),actual,"%zu")


void test_push_pop(){
	Vector<int*> v;
	int *p[3];
	for(int i = 0; i < 3; i++){
		p[i] = new int [5];
		for(int j = 0; j < 5; j++){
			p[i][j] = j;
		}
	}
	for(int i = 0; i < 3; i++)	v.push_back(p[i]);
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			TEST_INT(j, v[i][j]);
		}
	}
	for(int i = 0; i < 3; i++)	v.pop_back();
	TEST_INT(1, v.empty());
}


int main(){
	test_push_pop();
	//test_size();
	//test_iterator();
	//test_erase();
	//test_insert();
	printf("%d/%d (%3.2f%%) passed\n", test_pass, test_count, test_pass * 100.0 / test_count);
    return main_ret;
}

