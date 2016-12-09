#include <cstddef>	/* size_t */

#ifndef __VECTOR_H_
#define __VECTOR_H_

template <class T>
class Vector {//primary template
private:
	typedef T value_type;

public:
	inline value_type add(value_type a, value_type b){
		return a + b;
	}
};


template <class T>
class Vector<T*> {//partial specialization where T is a pointer
private:
	typedef T value_type;

public:
	inline value_type add(value_type a, value_type b){
		return a + b + 1;
	}
};

#endif