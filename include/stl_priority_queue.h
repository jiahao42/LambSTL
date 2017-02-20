#ifndef __LAMB_STL_INTERNAL_PRIORITY_QUEUE_H_
#define __LAMB_STL_INTERNAL_PRIORITY_QUEUE_H_

#include "stl_algorithm.h"
#include "stl_vector.h"
#include "stl_heap.h"

template <class T, class Sequence = Vector<T>, class Compare = less<typename Sequence::value_type>>
class Priority_Queue {
public:
	typedef typename Sequence::value_type value_type;
	typedef typename Sequence::size_type size_type;
	typedef typename Sequence::reference reference;
	typedef typename Sequence::const_reference const_reference;
protected:
	Sequence c;
	Compare comp;
public:
	Priority_Queue(): c() {}
	explicit Priority_Queue(const Compare& x) : c(), comp(x) {}
	
	template <class InputIterator>
	Priority_Queue(InputIterator first, InputIterator last, const Compare& x) : c(first, last), comp(x) { make_heap(c.begin(), c.end(), comp); }
	Priority_Queue(InputIterator first, InputIterator last) : c(first, last) { make_heap(c.begin(), c.end(), comp); }
	
	bool empty() const { return c.empty(); }
	size_type size() const { return c.size(); }
	const_reference top() const { return c.front(); }
	void push(const value_type& x){
		__STL_TRY {
			c.push_back(x);
			push_heap(c.begin(), c.end(), comp);
		}
		__STL_UNWIND(c.clear());
	}
	void pop() {
		__STL_TRY {
			pop_heap(c.begin(), c.end(), comp);
			c.pop_back();
		}
		__STL_UNWIND(c.clear());
	}
};















#endif

