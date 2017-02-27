#include "vector"
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
			p[i][j] = j;//[0,1,2,3,4] * 3
		}
	}
	for(int i = 0; i < 3; i++)	v.push_back(p[i]);
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 5; j++){
			TEST_INT(j, v[i][j]);
		}
	}
	for(int i = 0; i < 3; i++)	v.pop_back();
	TEST_INT(1, v.empty());
	for (int i = 0; i < 3; i++){
		delete[] p[i];
	}
}

void test_size(){
	Vector<int*> v;
	int *p = NULL;
	TEST_SIZE_TYPE(0, v.size());
	TEST_SIZE_TYPE(0, v.capacity());
	v.push_back(p);
	v.push_back(p);
	v.push_back(p);
	TEST_SIZE_TYPE(3, v.size());
	TEST_SIZE_TYPE(4, v.capacity());
	v.push_back(p);
	v.push_back(p);
	TEST_SIZE_TYPE(5, v.size());
	TEST_SIZE_TYPE(8, v.capacity());
	v.clear();
	TEST_SIZE_TYPE(0, v.size());
	TEST_SIZE_TYPE(8, v.capacity());//still 8
}

void test_iterator(){
	Vector<int*> v;
	int *p = new int[1];
	*p = 0;
	TEST_INT(1,v.empty());
	for (int i = 0; i < 30; i++){
		v.push_back(p);
	}
	Vector<int*>::iterator begin = v.begin();
	Vector<int*>::iterator end = v.end();
	for (int i = 0; i < 30; i++){
		TEST_INT(0, **begin++);
	}
	for (int i = 29; i != 0; i--){
		TEST_INT(0, **--end);
	}
	delete[] p;
}

void test_erase(){
	/* TEST iterator erase(iterator position) */
	Vector<int*> v;
	int *p = new int[1];
	*p = 0;
	for (int i = 0; i < 30; i++){
		v.push_back(p);
	}
	for (int i = 1; i < 30; i++){
		int temp = **v.erase(v.begin());
		TEST_INT(0, temp);
	}
	
	/* TEST iterator erase(iterator first, iterator last) */
	for (int i = 0; i < 30; i++){
		v.push_back(p);
	}
	v.erase(v.begin(), v.begin() + 10);
	for (int i = 10; i < 30; i++){
		TEST_INT(0, *v[i - 10]);
	}
	
	v.clear();
	TEST_INT(1,v.empty());
}

void test_insert(){
	/*
	Test capacity
	const size_type len = old_size + max(old_size, n);	
	*/
	Vector<int*> v;
	int *p = new int[1];
	*p = 0;
	v.insert(v.begin(), 10, p);//capacity += 10
	for(int i = 0; i < 10; i++){
		TEST_INT(0,*v[i]);
	}
	TEST_SIZE_TYPE(10,v.size());
	TEST_SIZE_TYPE(10,v.capacity());
	v.insert(v.begin(), 20, p);//capacity += 20
	TEST_SIZE_TYPE(30, v.capacity());
	v.insert(v.begin(), 5, p);//vector should double it's capacity
	TEST_SIZE_TYPE(60, v.capacity());
	for(int i = 0; i < 35; i++){
		TEST_INT(0, *v[i]);
	}
}

int main(){
	test_push_pop();
	test_size();
	test_iterator();
	test_erase();
	test_insert();
	printf("%d/%d (%3.2f%%) passed\n", test_pass, test_count, test_pass * 100.0 / test_count);
    return main_ret;
}

