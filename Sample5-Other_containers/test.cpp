#include "stack"
#include "queue"
#include "heap"
#include "vector"
#include "slist"
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

void test_heap(){
	size_t i;
	const int init[9] = {0, 1, 2, 3, 4, 8, 9, 3, 5};
	Vector<int> v;
	for (i = 0; i < sizeof(init) / sizeof(*init); i++){
		v.push_back(init[i]);
	}
	make_heap(v.begin(), v.end());
	/*
			 9 
		  /    \
		 5      8
	   /  \    /  \
	  3   4   0    2
	 / \
	3	1
	
	*/
	const int result_1[v.size()] = {9, 5, 8, 3, 4, 0, 2, 3, 1};
	for (i = 0; i < v.size(); i++){
		TEST_INT(result_1[i], v[i]);
	}
	
	v.push_back(7);
	push_heap(v.begin(), v.end());
	/*
	先将7插入末尾，然后执行上溯：若遇到比7小的结点，则交换之
				 9 
			  /     \
			7        8
		  /   \    /   \
		 3    5   0    2
	   /  \  /
	  3	  1 4
	
	*/
	const int result_2[v.size()] = {9, 7, 8, 3, 5, 0, 2, 3, 1, 4};
	for (i = 0; i < v.size(); i++){
		TEST_INT(result_2[i], v[i]);
	}
	
	pop_heap(v.begin(), v.end());
	TEST_INT(9, v[v.size() - 1]);
	v.pop_back();
	/*
	将根节点9与其左右孩子中较大者对调，直到到达叶子节点
	将数组末尾的数字放到该叶子节点中，进行上溯
				 8 
			  /     \
			7        4
		  /   \    /   \
		 3    5   0    2
	   /  \  
	  3	  1
	*/
	const int result_3[v.size()] = {8, 7, 4, 3, 5, 0, 2, 3, 1};
	for (i = 0; i < v.size(); i++){
		TEST_INT(result_3[i], v[i]);
	}
	
	const int result_4[v.size()] = {0, 1, 2, 3, 3, 4, 5, 7, 8};
	sort_heap(v.begin(), v.end());
	for (i = 0; i < v.size(); i++){
		TEST_INT(result_4[i], v[i]);
	}
}

# if 0
void test_priority_queue() {
	const int init[9] = {0, 1, 2, 3, 4, 8, 9, 3, 5};
	Priority_Queue<int> p;
	for (int i : init)	p.push(i);
	/*
				 9 
			  /     \
			8        5
		  /   \    /   \
		 4    3   3    2
	   /  \  
	  1	  0
	*/
	const int result[9] = {9, 8, 5, 4, 3, 3, 2, 1, 0};
	for (int i = 0; i < p.size(); i++){
		TEST_INT(result[i], p.top());
		p.pop();
	}
}
# endif

void test_slist() {
	Slist<int> s;
	TEST_INT(1, s.empty());
	for (int i = 0; i < 10; i++){
		s.push_front(i);
		TEST_INT(i, *s.begin());
	}
	TEST_SIZE_TYPE(10, s.size());
	for (int i = 0; i < 5; i++){
		TEST_INT(9 - i, *s.begin());
		s.pop_front();
	}
	TEST_SIZE_TYPE(5, s.size());
	s.clear();
	TEST_INT(1, s.empty());
}

int main(){
	test_stack();
	test_queue();
	test_heap();
	//test_priority_queue();
	test_slist();
	printf("%d/%d (%3.2f%%) passed\n", test_pass, test_count, test_pass * 100.0 / test_count);
    return main_ret;
}

