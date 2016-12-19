#include "vector.h"
#include "list.h"
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


void test_vector_push_pop(){
	Vector<int*> v;
	
	TEST_INT(1,v.empty());
	
	for (int i = 0; i < 30; i++){
		v.push_back(i);
		TEST_INT(i, v[i]);
	}
	
	TEST_INT(0,v.empty());
	
	for (int i = 29; i >= 0; i--){
		v.pop_back();
		TEST_INT(i, v[i]);
	}
	
	TEST_INT(1,v.empty());
}

void test_vector_size(){
	Vector<int*> v;
	
	TEST_INT(1,v.empty());
	TEST_SIZE_TYPE(0,v.capacity());
	
	v.push_back(1);
	TEST_SIZE_TYPE(1,v.size());
	TEST_SIZE_TYPE(1,v.capacity());
	
	v.push_back(2);
	TEST_SIZE_TYPE(2,v.capacity());
	TEST_SIZE_TYPE(2,v.size());
	
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
	TEST_SIZE_TYPE(8,v.capacity());
	TEST_SIZE_TYPE(5,v.size());
	
	TEST_INT(0,v.empty());
}

void test_vector_iterator(){
	Vector<int*> v;
	
	TEST_INT(1,v.empty());
	for (int i = 0; i < 30; i++){
		v.push_back(i);
	}
	Vector<int>::iterator begin = v.begin();
	Vector<int>::iterator end = v.end();
	for (int i = 0; i < 30; i++){
		TEST_INT(i, *begin++);
	}
	for (int i = 29; i != 0; i--){
		TEST_INT(i, *--end);
	}
}

void test_vector_erase(){
	/* TEST iterator erase(iterator position) */
	Vector<int*> v;
	for (int i = 0; i < 30; i++){
		v.push_back(i);
	}
	for (int i = 1; i < 30; i++){
		int temp = *v.erase(v.begin());
		TEST_INT(i, temp);
	}
	
	/* TEST iterator erase(iterator first, iterator last) */
	for (int i = 0; i < 30; i++){
		v.push_back(i);
	}
	v.erase(v.begin(), v.begin() + 10);
	for (int i = 10; i < 30; i++){
		TEST_INT(i - 1, v[i - 10]);
	}
	
	v.clear();
	TEST_INT(1,v.empty());
}

void test_vector_insert(){
	/*
	Test capacity
	const size_type len = old_size + max(old_size, n);	
	*/
	Vector<int> v;
	v.insert(v.begin(), 10, 1);//capacity += 10
	for(int i = 0; i < 10; i++){
		TEST_INT(1,v[i]);
	}
	TEST_SIZE_TYPE(10,v.size());
	TEST_SIZE_TYPE(10,v.capacity());
	v.insert(v.begin(), 20, 1);//capacity += 20
	TEST_SIZE_TYPE(30, v.capacity());
	v.insert(v.begin(), 5, 1);//vector should double it's capacity
	TEST_SIZE_TYPE(60, v.capacity());
	for(int i = 0; i < 35; i++){
		TEST_INT(1, v[i]);
	}
}

void test_list_push_back(){
	list<int> list;
	list.push_back(1);
	auto i = list.begin();
	TEST_INT(1, *i);
}

int main(){
	test_vector_push_pop();
	test_vector_size();
	test_vector_iterator();
	test_vector_erase();
	test_vector_insert();
	test_list_push_back();
	printf("%d/%d (%3.2f%%) passed\n", test_pass, test_count, test_pass * 100.0 / test_count);
    return main_ret;
}

