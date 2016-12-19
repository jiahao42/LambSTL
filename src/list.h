#ifndef __LIST_H_
#define __LIST_H_
#include <cstddef>	/* size_t */
#include "simple_alloc.h"
#include "iterator.h"
#include "construct.h"
#include "uninitialized.h"
#include "algorithm.h"

template <class T>
struct __list_node {//list结点，双向链表
	typedef void* void_pointer;
	void_pointer prev;
	void_pointer next;
	T data;
};

template<class T, class Ref, class Ptr>
struct __list_iterator {
	typedef __list_iterator<T, T&, T*>	iterator;
	typedef __list_iterator<T, Ref, Ptr>	self;
	
	typedef bidirectional_iterator_tag iterator_category;
	typedef T value_type;
	typedef Ptr pointer;
	typedef Ref reference;
	typedef __list_node<T>* link_type;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
	
	link_type node;
	
	//constructor
	__list_iterator(link_type x) : node(x) {}
	__list_iterator() {}
	__list_iterator(const iterator& x) : node(x.node) {}
	
	bool operator== (const self& x) const { return node == x.node; }
	bool operator!= (const self& x) const { return node != x.node; }
	reference operator*() const { return (*node).data; }
	pointer operator->() const { return &(operator*()); }
	
	self& operator++(){
		node = (link_type)((*node).next);
		return *this;
	}
	
	self operator++(int){
		self tmp = *this;
		++*this;
		return tmp;
	}
	
	self& operator--(){
		node =  (link_type)((*node).prev);
		return *this;
	}
	
	self operator--(int){
		self tmp = *this;
		--*this;
		return tmp;
	}
};

template <class T, class Alloc = alloc>
class list {
protected:
	typedef __list_node<T> list_node;
	typedef simple_alloc<list_node, Alloc> list_node_allocator;
public:
	typedef list_node* link_type;
	typedef T value_type;
	typedef value_type* pointer;
	typedef value_type& reference;
	typedef const value_type& const_reference;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
	typedef __list_iterator<T, T&, T*> iterator;
	typedef __list_iterator<T, const T&, const T*> const_iterator;
protected:
	link_type node;
	link_type get_node(){
		return list_node_allocator::allocate();
	}
	void put_node(link_type p){
		list_node_allocator::deallocate(p);
	}
	link_type create_node(const T& x){
		link_type p = get_node();
		construct(&p -> data, x);
		return p;
	}
	void destroy_node(link_type p){
		destroy(&p -> data);
		put_node(p);
	}
	void empty_initialize(){
		node = get_node();
		node -> next = node;
		node -> prev = node;
	}
public:
	list() { empty_initialize(); }
	iterator begin(){
		return (link_type)((*node).next);
	}
	iterator end(){
		return node;
	}
	bool empty() const {
		return node -> next == node;
	}
	
	size_type size() const {
		size_type result = 0;
		distance(begin(), end(), result);
		return result;
	}
	reference front() { return *begin(); }
	reference back() { return *(--end()); }
	void push_back(const T& x){	insert(end(),x); }
	iterator insert(iterator position, const T& x){
		link_type tmp = create_node(x);
		tmp -> next = position.node;
		tmp -> prev = position.node -> prev;
		(link_type(position.node -> prev))->next = tmp;
		position.node -> prev = tmp;
		return tmp;
	}
};





#endif
