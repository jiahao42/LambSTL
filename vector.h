#ifndef __VECTOR_H_
#define __VECTOR_H_
#include <cstddef>	/* size_t */
#include "simple_alloc.h"
#include "iterator.h"

template <class T, class Alloc = alloc>
class Vector {//primary template
public:
	typedef T value_type;
	typedef value_type* pointer;
	typedef value_type* iterator;
	typedef const value_type* const_iterator;
	typedef value_type& reference;
	typedef size_t	size_type;
	typedef ptrdiff_t	difference_type;

	inline value_type add(value_type a, value_type b){
		return a + b;
	}
protected:
	typedef simple_alloc<value_type,alloc> data_allocator;
	iterator start;
	iterator finish;
	iterator end_of_storage;
	void insert_aux(iterator position, const T& x){}
	void deallocate(){
		if (start)
			data_allocator::deallocate(start,end_of_storage - start);
	}
	void fill_initialize(size_type n, const T& value){
		//start = allocate_and_fill(n,value);
		finish = start + n;
		end_of_storage = finish;
	}

public:
	iterator begin(){ return start; }
	const_iterator begin() const { return start; }
	iterator end() { return finish; }
	const_iterator end() const { return finish; }
	size_type size() const { return size_type(end() - begin()); }
	size_type capacity() const {
		return size_type(end_of_storage - begin());
	}
	bool empty() const { return begin() == end();}
	reference operator[](size_type n){ return *(begin() + n); }
	Vector():start(0),finish(0), end_of_storage(0){}
	~Vector(){
		//destroy(start,finish);
		deallocate();
	}
};


template <class T>
class Vector<T*> {//partial specialization where T is a pointer
public:
	typedef T 			value_type;
	typedef value_type* pointer;
	typedef value_type* iterator;
	typedef const value_type* const_iterator;
	typedef value_type& reference;
	typedef size_t		size_type;
	typedef ptrdiff_t	difference_type;

	inline value_type add(value_type a, value_type b){
		return a + b;
	}
protected:
	typedef simple_alloc<value_type,alloc> data_allocator;
	iterator start;
	iterator finish;
	iterator end_of_storage;
	void insert_aux(iterator position, const T& x){}
	void deallocate(){
		//std::cout<<"deallocate!"<<std::endl;
		if (start)
			data_allocator::deallocate(start,end_of_storage - start);
	}
	void fill_initialize(size_type n, const T& value){}

public:
	iterator begin(){ return start; }
	const_iterator begin() const { return start; }
	iterator end() { return finish; }
	const_iterator end() const { return finish; }
	size_type size() const { return size_type(end() - begin()); }
	size_type capacity() const {
		return size_type(end_of_storage - begin());
	}
	bool empty() const { return begin() == end();}
	reference operator[](size_type n){ return *(begin() + n); }
	Vector() : start(0),finish(0), end_of_storage(0){}
	~Vector(){
		//destroy(start,finish);
		deallocate();
	}
};

#endif