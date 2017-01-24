#ifndef __SLIST_H_
#define __SLIST_H_

#include "simple_alloc.h"
#include "iterator.h"

struct __slist_node_base {
	__slist_node_base* next;
};

template <class T>
struct __slist_node : public __slist_node_base {
	T data;
};

inline __slist_node_base* __slist_make_link(__slist_node_base* prev_node, __slist_node_base* new_node) {
	new_node -> next = prev_node -> next;
	prev_node -> next = new_node;
	return new_node;//prev->new->...
}

inline size_t __slist_size(__slist_node_base* node) {
	size_t result = 0;
	for (; node != 0; node = node -> next)
		result++;
	return result;
}

struct __slist_iterator_base {
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
	typedef forward_iterator_tag iterator_category;
	
	__slist_node_base* node;
	__slist_iterator_base(__slist_node_base* x) : node(x) {}
	
	void incr() { node = node -> next; }
	bool operator== (const __slist_iterator_base& x) const {
		return node == x.node;
	}
	bool operator!= (const __slist_iterator_base& x) const {
		return node != x.node;
	}
};


template <class T, class Ref, class Ptr>
struct __slist_iterator : public __slist_iterator_base {
	typedef __slist_iterator<T, T&, T*>		iterator;
	typedef __slist_iterator<T, const T&, const T*> const_iteartor;
	typedef __slist_iterator<T, Ref, Ptr>	self;
	
	typedef T value_type;
	typedef Ptr pointer;
	typedef Ref reference;
	typedef __slist_node<T> list_node;
	
	__slist_iterator(list_node* x) : __slist_iterator_base(x) {}
	__slist_iterator() : __slist_iterator_base(0) {}
	__slist_iterator(const iterator& x) : __slist_iterator_base(x.node) {}
	
	reference operator*() const { return ((list_node*)node)->data; }
	pointer operator->() const { return &(operator*()); }
	
	self& operator++(){
		incr();
		return *this;
	}
	
	self operator++(int){
		self tmp = *this;
		incr();
		return tmp;
	}
};


template <class T, class Alloc = alloc>
class Slist {
public:
	typedef T value_type;
	typedef value_type* pointer;
	typedef const value_type* const_pointer;
	typedef value_type& reference;
	typedef const value_type& const_reference;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
	
	typedef __slist_iterator<T, T&, T*> iterator;
	typedef __slist_iterator<T, const T&, const T*> const_iteartor;
	
private:
	typedef __slist_node<T> list_node;
	typedef __slist_node_base list_node_base;
	typedef __slist_iterator_base iterator_base;
	typedef simple_alloc<list_node, Alloc> list_node_allocator;
	
	static list_node* create_node(const value_type& x) {
		list_node* node = list_node_allocator::allocate();
		__STL_TRY {
			construct(&node->data, x);
			node -> next = 0;
		}
		__STL_UNWIND(list_node_allocator::deallocate(node));
		return node;
	}
	
	static void destroy_node(list_node* node) {
		destroy(&node -> data);
		list_node_allocator::deallocate(node);
	}
private:
	list_node_base head;

public:
	Slist() { head.next = 0; }
	~Slist() { clear(); }
	
public:
	iterator begin() {
		return iterator((list_node*)head.next); 
	}
	iterator end() {
		return iterator(0);
	}
	size_type size() const {
		return __slist_size(head.next); 
	}
	bool empty() const { return head.next == 0; }
	
	void swap(Slist& L){
		list_node_base* tmp = head.next;
		head.next = L.head.next;
		L.head.next = tmp;
	}
public:
	reference front() { return ((list_node*)head.next)->data; }
	void push_front(const value_type& x) {//从头部插入元素
		__slist_make_link(&head, create_node(x));//head->new->...
	}
	
	//no push_back
	
	void pop_front(){
		list_node* node = (list_node*) head.next;
		head.next = node -> next;
		destroy_node(node);
	}
	
	void clear() {
		for (int i = 0; i < size(); i++){
			pop_front();
		}
		head.next = 0;
	}
};



#endif