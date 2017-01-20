#include "stack.h"
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

template <class T, class Sequence = Deque<T>>
void _test_stack(Stack<T, Sequence> s){
	TEST_INT(1, s.empty());
	for (int i = 0; i < 10; i++){
		//TEST_SIZE_TYPE(i, s.size());
		s.push(i);
		TEST_SIZE_TYPE(i + 1, s.size());
		TEST_INT(i, s.top());
	}
	TEST_INT(0, s.empty());
	for (int i = 0; i < 10; i++){
		TEST_SIZE_TYPE(10 - i, s.size());
		TEST_INT(9 - i, s.top());
		s.pop();
	}
	TEST_INT(1, s.empty());
}

void test_stack(){
	Stack<int> s_deque;
	_test_stack(s_deque);
	
	Stack<int, List<int>> s_list;
	_test_stack(s_list);
	
	Stack<int, Vector<int>> s_vector;
	_test_stack(s_vector);


}

int main(){
	test_stack();
	printf("%d/%d (%3.2f%%) passed\n", test_pass, test_count, test_pass * 100.0 / test_count);
    return main_ret;
}

