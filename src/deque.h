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
	
public:
	void set_node(map_pointer new_node){
		node = new_node;
		first = *new_node;
		last = first + difference_type(buffer_size());
	}
	
	reference operator*() const { return *cur; }
	pointer operator-> const { return &(operator*()); }
	difference_type operator- (const self& x) const {
		return difference_type(buffer_size()) * (node - x.node - 1) + (cur - first) + (x.last - x.cur);
	}
	
	//pre
	self& operator++(){
		++cur;
		if (cur == last){
			set_node(node + 1);
			cur = first;
		}
		return *this;
	}
	
	self operator++(int) {
		self tmp = *this;
		++*this;
		returm tmp;
	}
	
	self& operator-- () {
		if (cur == first){
			set_node(node - 1);
			cur = first;
		}
		--cur;
		return *this;
	}
	
	self operator-- (int) {
		self tmp = *this;
		--*this;
		return tmp;
	}
	
	self& operator+=(difference_type n){
		difference_type offset = n + (cur - first);
		if (offset >= 0 && offset < difference_type(buffer_size()))
			cur+=n;
		else{
			difference_type node_offset = offset > 0 ? offset / difference_type(buffer_size()) : -difference_type((-offset - 1) / buffer_size()) - 1;
			set_node(node + node_offset);
			cur = first + (offset - node_offset * difference_type(buffer_size()));
		}
		return *this;
	}
	
	self operator+ (difference_type n)	const {
		self tmp = *this;
		return tmp += n;
	}
	
	self& operator-=(difference_type n ){
		return *this += -n;
	}
	
	self operator- (difference_type n ) const {
		self tmp = *this;
		return tmp -= n;
	}
	
	reference operator[] (difference_type n) const {
		return *(*this + n);
	}
	
	bool operator== (const self& x)	const { return cur == x.cur; }
	bool operator!= (const self& x) const { return !(*this == x); }
	bool operator< (const self& x) const {
		return (node == x.node) ? (cur < x.cur) : (node < x.node);
	}

};





#endif