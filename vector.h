#include <cstddef>	/* size_t */

#ifndef __VECTOR_H_
#define __VECTOR_H_

template <class T, class Alloc = alloc>
class Vector {//primary template
private:

public:
	typedef T value_type;
	typedef value_type* pointer;
	typedef value_type* iterator;
	typedef value_type& reference;
	typedef size_t	size_type;
	typedef ptrdiff_t	difference_type;

	inline value_type add(value_type a, value_type b){
		return a + b;
	}
protected:

};


template <class T>
class Vector<T*> {//partial specialization where T is a pointer
private:
	typedef T value_type;

public:
	inline value_type add(value_type a, value_type b){
		return a + b;
	}
};

#endif