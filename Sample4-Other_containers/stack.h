#ifndef __STACK_H_
#define __STACK_H_

#include <cstddef>	/* size_t */
#include "deque.h" /* Deque */
#include "simple_alloc.h" /* alloc */
#include "iterator.h"	/* __true_type __false_type */
#include "construct.h"  /* construct() destroy() */
#include "algorithm.h"

template <class T, class Sequence = Deque<T> >
class Stack {
	friend bool operator== __STL_NULL_TMPL_ARGS (const Stack&, const Stack&);
	friend bool operator< __STL_NULL_TMPL_ARGS (const Stack&, const Stack&);
public:
	typedef typename Sequence::value_type value_type;
	typedef typename Sequence::size_type size_type;
	typedef typename Sequence::reference reference;
	typedef typename Sequence::const_reference const_reference;
protected:
	Sequence c;
public:
	bool empty() const { return c.empty(); }
	size_type size() const { return c.size(); }
	reference top() { return c.back(); }
	const_reference top() const { return c.back(); }
	void push(const value_type& x) { c.push_back(x); }
	void pop() { c.pop_back(); }
};

template <class T, class Sequence>
bool operator== (const Stack<T, Sequence>& x, const Stack<T, Sequence>& y){
	return x.c == y.c;
}

template <class T, class Sequence>
bool operator< (const Stack<T, Sequence>& x, const Stack<T, Sequence>& y){
	return x.c < y.c;
}

#endif