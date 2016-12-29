#ifndef __DEQUE_H_
#define __DEQUE_H_

#include <cstddef>	/* size_t */
#include "simple_alloc.h" /* alloc */
#include "iterator.h"	/* __true_type __false_type */
#include "construct.h"  /* construct() destroy() */

template <class T, class Ref, class Ptr, size_t BufSiz>
struct __deque_iterator {
	typedef __deque_iterator<T, T&, T*, BufSiz> iterator;
	typedef __deque_iterator<T, const T&, const T*, BufSiz> const_iterator;
	static size_t buffer_size()	{ return __deque_buf_size(BufSiz, sizeof(T)); }
	
	typedef random_access_iterator_tag iterator_category;
	typedef T value_type;
	typedef Ptr pointer;
	typedef Ref	reference;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
	typedef T** map_pointer;
	
	typedef __deque_iterator self;
	
	T* cur;
	T* first;
	T* last;
	map_pointer node;
	
	inline size_t __deque_buf_size(size_t n, size_t sz){
		return n != 0 ? n : (sz < 512 ? size_t(512 / sz) : size_t (1));
	}
};


template <class T, class Alloc = alloc, size_t BufSiz = 0>
class deque {

public:
	typedef T value_type;
	typedef value_type* pointer;
	
protected:
	typedef pointer* map_pointer;
	
protected:
	map_pointer map;
	size_type map_size;

};





#endif