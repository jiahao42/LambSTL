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
	//为什么要分Ref,Ptr 与 T&,T*
	//Ref = const T& Ptr = const T*
	//而不影响iterator
	typedef __list_iterator<T, T&, T*>	iterator;
	typedef __list_iterator<T, Ref, Ptr>	self;
	
	typedef bidirectional_iterator_tag iterator_category;//不是原生指针，不支持随机存储
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
	reference operator*() const { return (*node).data; }//返回reference，返回左值
	pointer operator->() const { return &(operator*()); }//迭代器成员存取(member access)的标准做法
	
	//pre-increment operator
	self& operator++(){//移动自身，返回左值引用
		node = (link_type)((*node).next);
		return *this;
	}
	//post-increment operator
	self operator++(int){//移动结点，返回右值
		self tmp = *this;
		++*this;
		return tmp;
	}
	
	//pre-increment operator
	self& operator--(){
		node =  (link_type)((*node).prev);
		return *this;
	}
	
	//post-increment operator
	self operator--(int){
		self tmp = *this;
		--*this;
		return tmp;
	}
};

template <class T, class Alloc = alloc>
class List {
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
	void empty_initialize(){//初始化，申请一个空间，两个指针指向自身
		node = get_node();
		node -> next = node;
		node -> prev = node;
	}
public:
	List() { empty_initialize(); }
	iterator begin(){
		return (link_type)((*node).next);//node是尾端的空白结点
	}
	const_iterator begin() const {
		return (link_type)((*node).next);
	}
	const_iterator end() const {
		return node;
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
	reference front() { return *begin(); }//head的值
	reference back() { return *(--end()); }//tail的值
	iterator insert(iterator position, const T& x){//只插入一个点
		link_type tmp = create_node(x);
		tmp -> next = position.node;
		tmp -> prev = position.node -> prev;
		(link_type(position.node -> prev))->next = tmp;
		position.node -> prev = tmp;
		return tmp;//将数据插入在position前方，插入后返回插入数据
	}
	void push_front(const T& x){ insert(begin(), x); }
	void push_back(const T& x) { insert(end(), x); }
	iterator erase(iterator position){//移除position所在节点，并返回下一个节点的迭代器
		link_type next_node = link_type(position.node -> next);
		link_type prev_node = link_type(position.node -> prev);
		prev_node -> next = next_node;
		next_node -> prev = prev_node;
		destroy_node(position.node);
		return iterator(next_node);
	}
	void pop_front(){
		erase(begin());
	}
	void pop_back(){
		iterator tmp = end();
		erase(--tmp);
	}
	
	void clear(){
		link_type cur = (link_type)node -> next;
		while (cur != node){
			link_type tmp = cur;
			cur = (link_type)cur -> next;
			destroy_node(tmp);
		}
		node -> next = node;
		node -> prev = node;
	}
	
	void remove(const T& value){//将值为value的所有元素移除
		iterator first = begin();
		iterator last = end();
		while (first != last){
			iterator next = first;
			++next;
			if (*first == value)	erase(first);
			first = next;
		}
	}
	
	void unique(){
		iterator first = begin();
		iterator last = end();
		if (first == last)	return;//empty
		iterator next = first;
		while (++next != last){
			if (*first == *next)
				erase(next);
			else
				first = next;
			next = first;
		}
	}
	
	/* This function is not standard stl, just for convenience */
	iterator operator[] (size_type n){//根据下标返回迭代器
		int count = 0;
		iterator cur = begin();
		while (count != n){
			cur++;
			count++;
		}
		return cur;
	}
};





#endif
