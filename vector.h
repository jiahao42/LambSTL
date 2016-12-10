#ifndef __VECTOR_H_
#define __VECTOR_H_
#include <cstddef>	/* size_t */
#include "simple_alloc.h"
#include "iterator.h"

template <class T, class Alloc = alloc>
class Vector {//primary template
public:
	typedef T value_type;
	typedef value_type* iterator;
	typedef size_t	size_type;

	inline value_type add(value_type a, value_type b){
		return a + b;
	}
protected:
	typedef simple_alloc<value_type,alloc> data_allocator;
	iterator start;
	iterator finish;
	iterator end_of_storage;

public:
	iterator begin(){return start;}
	iterator end()	{ return finish; }
	size_type size() const { return size_type(end() - begin()); }
	Vector():start(0),finish(0), end_of_storage(0){}
};

#endif