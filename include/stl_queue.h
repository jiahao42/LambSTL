#ifndef QUEUE_H_
#define QUEUE_H_

#include <iostream> /* std::cout */
#include "stl_deque.h"	/* Deque */
#include "stl_list.h"	/* List */


// forward declare the Queue
template <class T, class Sequence>
class Queue;

template <class T, class Sequence>
bool operator== (const Queue<T, Sequence>& x, const Queue<T, Sequence>& y){
	return x.c == y.c;
}

template <class T, class Sequence>
bool operator< (const Queue<T, Sequence>& x, const Queue<T, Sequence>& y){
	return x.c < y.c;
}

template <class T, class Sequence = Deque<T>>
class Queue {
	friend bool operator== __STL_NULL_TMPL_ARGS (const Queue& x, const Queue& y);
	friend bool operator< __STL_NULL_TMPL_ARGS (const Queue& x, const Queue& y);
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
	reference front() { return c.front(); }
	const_reference front() const { return c.front(); }
	reference back() { return c.back(); }
	const_reference back() const { return c.back(); }
	void push(const value_type& x) { c.push_back(x); }
	void pop() { c.pop_front(); }
};












#endif