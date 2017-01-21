#include "stack.h"
#include "queue.h"
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
void test_stack_aux(Stack<T, Sequence>& s){
	TEST_INT(1, s.empty());
	for (int i = 0; i < 10; i++){
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

template <class T, class Sequence = Deque<T>>
void test_queue_aux(Queue<T, Sequence>& s){
	TEST_INT(1, s.empty());
	for (int i = 0; i < 10; i++){
		s.push(i);
		TEST_SIZE_TYPE(i + 1, s.size());
		TEST_INT(i, s.back());
	}
	TEST_INT(0, s.empty());
	for (int i = 0; i < 10; i++){
		TEST_SIZE_TYPE(10 - i, s.size());
		TEST_INT(i, s.front());
		s.pop();
	}
	TEST_INT(1, s.empty());
}

void test_stack(){
	Stack<int> s_deque;
	test_stack_aux(s_deque);
	
	Stack<int, List<int>> s_list;
	test_stack_aux(s_list);
	
	Stack<int, Vector<int>> s_vector;
	test_stack_aux(s_vector);
}

void test_queue(){
	Queue<int> s_deque;
	test_queue_aux(s_deque);
	
	Queue<int, List<int>> s_list;
	test_queue_aux(s_list);
}

int main(){
	test_stack();
	test_queue();
	printf("%d/%d (%3.2f%%) passed\n", test_pass, test_count, test_pass * 100.0 / test_count);
    return main_ret;
}

