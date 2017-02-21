#include "list"
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

void test_list_iterator() {
	List<int> l;
	for (int i = 0; i < 20; i++) {
		l.push_back(i);
		TEST_INT(i, l.back());
	}
	auto it = l.begin();
	for (int i = 0; i < 20; i++) {
		TEST_INT(i, *it++);
	}
	for (int i = 19; i >=0; i--) {
		TEST_INT(i, *--it);
	}
}


void test_list_push_pop(){
	List<int> l;
	TEST_INT(1, l.empty());
	for(int i = 0; i < 30; i++){
		TEST_SIZE_TYPE(i, l.size());
		l.push_back(i);
		TEST_INT(i, l.back());
	}
	l.push_front(999);//[999,0,1,2,3,...]
	TEST_INT(999, *l[0]);
	TEST_INT(0, *l.erase(l[0]));//[0,1,2,3,...]

	
	TEST_INT(0, l.empty());
	l.clear();
	TEST_INT(1, l.empty());
}

void test_list_insert(){
	List<int> l;
	l.insert(l.begin(), 1);
	//after insert : [1]
	TEST_INT(1, l.front());
	TEST_INT(1, *l[0]);
	for(int i = 0; i < 30; i++){
		l.push_back(i);
	}
	//before insert : [1,0,1,2,3,4,5,6,7...]
	l.insert(l[5],100);
	//after insert : [1,0,1,2,3,100,4,5,6,7...]
	TEST_INT(3, *l[4]);
	TEST_INT(100, *l[5]);
	TEST_INT(4, *l[6]);
	
	l.clear();
	l.insert(l[0], 2, 10);
	TEST_SIZE_TYPE(10, l.size());
	for (int i = 0; i < l.size(); i++){
		TEST_INT(2, *l[i]);
	}
	l.insert(l[5], 1, 5);
	TEST_SIZE_TYPE(15, l.size());
	for (int i = 0; i < 5; i++){
		TEST_INT(1, *l[5 + i]);
	}
}

void test_list_remove(){
	List<int> l;
	for (int i = 0; i < 30; i++){
		if (i % 2){
			l.push_back(1);
		}else{
			l.push_back(2);
		}
	}//[2,1,2,1,2,1...]
	TEST_SIZE_TYPE(30, l.size());
	l.remove(1);//[2,2,2,2...]
	TEST_SIZE_TYPE(15, l.size());
	for (int i = 0; i < 15; i++){
		TEST_INT(2, *l[i]);
	}
	l.unique();
	TEST_SIZE_TYPE(1, l.size());
	TEST_INT(2, *l[0]);
}

void test_list_transfer(){
	List<int> l1;
	List<int> l2;
	for(int i = 0; i < 30; i++){
		l1.push_back(i);
		l2.push_back(i + 30);
	}//l1 : [0,1,2,3...]	l2 : [30,31,32,33...]
	l1.splice(l1[10], l2);//l1 : [0,1,2...,9,30,31,...59,10,11...29]
	for (int i = 10; i < 40; i++){
		TEST_INT(i + 20, *l1[i]);
	}
	l2.push_back(123);
	l1.splice(l1[23], l2, l2.begin());
	TEST_INT(123, *l1[23]);
	for (int i = 777; i > 766; i--){
		l2.push_back(i);
	}
	l1.splice(l1[5], l2, l2[2], l2[5]);
	TEST_INT(775, *l1[5]);
	TEST_INT(774, *l1[6]);
	TEST_INT(773, *l1[7]);
}

void test_list_swap(){
	List<int> l1;
	List<int> l2;
	//TODO
	for (int i = 0; i < 10; i++){
		l1.push_back(i);//[0,1,2,...,9]
		l2.push_back(9 - i);//[9,8,7,...,0]
	}
	l1.swap(l2);
	for (int i = 0; i < 10; i++){
		TEST_INT(i, *l2[i]);//[0,1,2,...,9]
		TEST_INT(9 - i, *l1[i]);//[9,8,7,...,0]
	}
}

void test_list_sort(){
	List<int> l;
	for (int i = 0; i < 30; i++)
		l.push_back(i);//[0,1,2,3...29]
	l.reverse();//[29,28,27,26...0]
	for (int i = 0; i < 30; i++){
		TEST_INT(29 - i, *l[i]);
	}
	l.sort();//[0,1,2,3...29]
	for (int i = 0; i < 30; i++)
		TEST_INT(i, *l[i]);
	
}

/* test List */
void test_list(){
	test_list_iterator();
	test_list_push_pop();
	test_list_insert();
	test_list_remove();
	test_list_transfer();
	test_list_swap();
	//test_list_sort();
}


int main(){
	test_list();
	printf("%d/%d (%3.2f%%) passed\n", test_pass, test_count, test_pass * 100.0 / test_count);
    return main_ret;
}

