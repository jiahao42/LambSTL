#include "deque.h"
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

void test_deque_push_pop(){
	LOG("**start to test deque push and pop...**", "", 0);
	Deque<int, alloc, 5> d;
	int i;
	d.push_back(1);
	TEST_INT(d[0],1);
	TEST_SIZE_TYPE(1, d.size());
	d.pop_back();
	TEST_SIZE_TYPE(0, d.size());
	for (i = 0; i < 5; i++){//[0,1,2,3,4]
		d.push_back(i);
		TEST_INT(i, d[i]);
	}
	for (i = 0; i < 5; i++){//[14,13,12,11,10,0,1,2,3,4]
		d.push_front(i + 10);
		TEST_INT(i + 10, d[0]);
	}
	for (i = 0; i < 5; i++){//[14,13,12,11,10]
		d.pop_back();
		TEST_INT(i, d[i + 5]);
	}
	for (i = 0; i < 5; i++){//[]
		TEST_INT(14 - i, d[0]);
		d.pop_front();
	}
	TEST_SIZE_TYPE(0, d.size());
	
	for (i = 0; i < 25; i++){
		d.push_back(i);//This will cause reallocation
	}
	cout<<endl;
}

void test_deque_size(){
	LOG("**start to test deque size...**", "", 0);
	Deque<int> d;
	TEST_SIZE_TYPE(512 / sizeof(int),d.begin().buffer_size());
	cout<<endl;
}

/* test Deque */
void test_deque(){
	test_deque_push_pop();
	test_deque_size();
	//test_deque_iterator();
	//test_deque_erase();
	//test_deque_insert();
}


int main(){
	test_deque();
	printf("%d/%d (%3.2f%%) passed\n", test_pass, test_count, test_pass * 100.0 / test_count);
    return main_ret;
}

