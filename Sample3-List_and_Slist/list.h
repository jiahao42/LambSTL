#ifndef LIST_H_
#define LIST_H_
#include <cstddef>	/* size_t */
#include "algorithm.h"
#include "simple_alloc.h" /* alloc */
#include "iterator.h"	/* __true_type __false_type */
#include "construct.h"	/* construct() destroy() */
#include <iostream> /* std::cout */

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
	
	//将[first,last)内所有元素移动到position之前
	//注意last是开区间
	void transfer(iterator position, iterator first, iterator last){
		if (position != last){
			(*(link_type((*last.node).prev))).next = position.node;
			(*(link_type((*first.node).prev))).next = last.node;
			(*(link_type((*position.node).prev))).next = first.node;
			link_type tmp = link_type((*position.node).prev);
			(*position.node).prev = (*last.node).prev;
			(*last.node).prev = (*first.node).prev;
			(*first.node).prev = tmp;
		}
	}
	
public:
	List() { empty_initialize(); }
	~List() {
		clear();
		put_node(node);
	}
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
	iterator insert(iterator position, const T& x, size_type n){//TODO : fix return value
		for (int i = 0; i < n; i++){
			insert(position, x);
		}
		return position;
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
	
	void unique(){//去除所有[连续而相同的元素]
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
	
	void splice(iterator position, List& x){//将x连接到position所指位置之前
		if (!x.empty()){
			transfer(position, x.begin(), x.end());
		}
	}
	
	void splice(iterator position, List&, iterator i){//将i所指元素接合到position之前
		iterator j = i;
		++j;
		if (position == i || position == j)	return;
		transfer(position, i, j);
	}
	
	void splice(iterator position, List&, iterator first, iterator last){//将first-last接合到position之前
		if (first != last){
			transfer(position, first, last);
		}
	}
	
	//进行merge的内容必须经过递增排序
	void merge(List& x){
		iterator first1 = begin();
		iterator last1 = end();
		iterator first2 = begin();
		iterator last2 = end();
		
		while (first1 != last1 && first2 != last2){
			if (*first2 < *first1){
				iterator next = first2;
				transfer(first1, first2, ++next);
				first2 = next;
			}else{
				++first1;
			}
			if (first2 != last2) transfer(last1, first2, last2);
		}
	}
	void reverse(){
		if (node -> next == node || link_type(node -> next) -> next == node)
			return;
		iterator first = begin();
		++first;
		while (first != end()){
			iterator old = first;
			++first;
			transfer(begin(), old, first);//不停将first插到头部
		}
	}
	
	void swap(List& x){
		List<T> tmp;
		tmp = x;
		x = *this;
		*this = tmp;
	}
	//quick sort
	void sort(){
		if (node -> next == node || link_type(node -> next) -> next == node)
			return;
		List<T> carry;
		List<T> counter[64];
		int fill = 0;
		while (!empty()){
			//std::cout<<"hello: "<<fill<<std::endl;
			carry.splice(carry.begin(), *this, begin());
			int i = 0;
			while (i < fill && !counter[i].empty()){
				counter[i].merge(carry);
				carry.swap(counter[i++]);
			}
			carry.swap(counter[i]);
			if (i == fill)	++fill;
		}
		for (int i = 1; i < fill; ++i){
			counter[i].merge(counter[i - 1]);
		}
		swap(counter[fill - 1]);
	}
	
	
	/* This function is not standard stl, just for convenience */
	iterator operator[] (size_type n){//根据下标返回迭代器，STL标准应该使用advance()来移动迭代器
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
