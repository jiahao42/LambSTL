#include <cstddef>	/* size_t */

#ifndef __VECTOR_H_
#define __VECTOR_H_

template <class T>
class Vector{
private:
	typedef T value_type;

public:
	inline value_type add(value_type a, value_type b){
		return a + b;
	}
};

#endif