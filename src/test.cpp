#include "vector.h"
#include "list.h"
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


void test_vector_push_pop(){
	Vector<int> v;
	
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
	Vector<int> v;
	
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
	Vector<int> v;
	
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
	Vector<int> v;
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
	List<int> l1,l2;
	for (int i = 0; i < 10; i++){
		l1.push_back(i);
		l2.push_back(9 - i);
	}
	l1.swap(l2);
	for (int i = 0; i < 10; i++){
		TEST_INT(i, *l2[i]);
		TEST_INT(9 - i, *l1[i]);
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

void test_list_vector_mixed(){
	/* Vector contains List */
	Vector<List<int>> v;
	List<int> l[3];
	for(int i = 0; i < 5; i++){
		l[0].push_back(i);//[0,1,2,3,4]
		l[1].push_back(i + 5);//[5,6,7,8,9]
		l[2].push_back(i + 10);//[10,11,12,13,14]
	}
	for (int i = 0; i < 3; i++)
		v.push_back(l[i]);
	TEST_INT(0, *v[0][0]);
	TEST_INT(0, *v[0].begin());
	TEST_INT(1, *v[0][1]);
	TEST_INT(5, *v[1][0]);
	TEST_INT(14, *v[2][4]);
	
	/* List contains Vector */
	List<Vector<int>> list;
	Vector<int> vectors[3];
	for(int i = 0; i < 5; i++){
		vectors[0].push_back(i);//[0,1,2,3,4]
		vectors[1].push_back(i + 5);//[5,6,7,8,9]
		vectors[2].push_back(i + 10);//[10,11,12,13,14]
	}
	for (int i = 0; i < 3; i++)
		list.push_back(vectors[i]);
	TEST_INT(0, (*list[0])[0]);
	TEST_INT(0, *(*list[0]).begin());
	TEST_INT(1, (*list[0])[1]);
	TEST_INT(5, (*list[1])[0]);
	TEST_INT(14, (*list[2])[4]);
	
	/* push several same one */
	list.push_back(vectors[0]);//list[3] = [0,1,2,3,4]
	list.push_back(vectors[0]);//list[4] = [0,1,2,3,4]
	list.push_back(vectors[0]);//list[5] = [0,1,2,3,4]
	for (int i = 0; i < 3; i++){
		for(int j = 0; j < 5; j++){
			TEST_INT(j, (*list[i + 3])[j]);
		}
	}

	/* Multiple Containers */
	List<int> inner_list_1;						// *((*((*(m_list[0]))[0][0]))[0][0])	//get inner_list_1
	List<List<int>> inner_list_2;				// (*((*(m_list[0]))[0][0]))[0]	//get inner_list_2
	Vector<List<List<int>>> inner_vector_1;		// *((*(m_list[0]))[0][0])	//get inner_vector_1
	List<Vector<List<List<int>>>> inner_list_3;	// (*(m_list[0]))[0]	//get inner_list_3
	Vector<List<Vector<List<List<int>>>>> inner_vector_2;// *(m_list[0])	//get inner_vector_2
	List<Vector<List<Vector<List<List<int>>>>>> m_list;
	for (int i = 0; i < 10; i++){
		inner_list_1.push_back(i);
	}
	inner_list_2.push_back(inner_list_1);
	inner_list_2.push_back(inner_list_1);
	inner_list_2.push_back(inner_list_1);
	inner_vector_1.push_back(inner_list_2);
	inner_list_3.push_back(inner_vector_1);
	inner_vector_2.push_back(inner_list_3);
	m_list.push_back(inner_vector_2);
	
	TEST_INT(0, *(*((*((*(m_list[0]))[0][0]))[0][0]))[0]);
	
	/*
	get m_list				m_list
	get inner_vector_2		*m_list.begin()
	get inner_list_3		*(*m_list.begin().begin())
	get inner_vector_1		*(*(*m_list.begin().begin()).begin())
	get inner_list_2		*(*(*(*m_list.begin().begin()).begin()).begin())
	get inner_list_1		*(*(*(*(*m_list.begin().begin()).begin()).begin()).begin())
	get element				*(*(*(*(*(*m_list.begin().begin()).begin()).begin()).begin()))[0]
	*/
	for (int i = 0; i < 10; i++){
		TEST_INT(i, *(*((*((*(m_list[0]))[0][0]))[0][0]))[i]);
		TEST_INT(i, *(*(*(*(*(*m_list.begin()).begin()).begin()).begin()).begin())[i]);
		TEST_INT(i, *(*(m_list.begin()->begin()->begin()->begin()->begin()))[i]);
	}
	
}

void test_deque_push_pop(){
	Deque<int> d;
	d.push_back(1);
	TEST_INT(d[0],1);
}

/* test Vector */
void test_vector(){
	test_vector_push_pop();
	test_vector_size();
	test_vector_iterator();
	test_vector_erase();
	test_vector_insert();
}

/* test List */
void test_list(){
	test_list_push_pop();
	test_list_insert();
	test_list_remove();
	test_list_transfer();
	test_list_swap();
	//test_list_sort();
}

/* test Deque */
void test_deque(){
	test_deque_push_pop();
	//test_deque_size();
	//test_deque_iterator();
	//test_deque_erase();
	//test_deque_insert();
}
int main(){
	test_vector();
	test_list();
	test_list_vector_mixed();
	test_deque();
	printf("%d/%d (%3.2f%%) passed\n", test_pass, test_count, test_pass * 100.0 / test_count);
    return main_ret;
}

