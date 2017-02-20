#ifndef VECTOR_H_
#define VECTOR_H_
#include <cstddef>	/* size_t */
#include "simple_alloc.h"
#include "iterator.h"
#include "construct.h"
#include "uninitialized.h"
#include <iostream>


template<class BidirectionalIterator1, class BidirectionalIterator2>
BidirectionalIterator2 copy_backward ( BidirectionalIterator1 first, BidirectionalIterator1 last, BidirectionalIterator2 result )
{
  while (last!=first) *(--result) = *(--last);
  return result;
}

template <class T, class Alloc = alloc>
class Vector {//primary template
public:
	typedef T 			value_type;
	typedef value_type* pointer;
	typedef value_type* iterator;
	typedef const value_type* const_iterator;
	typedef value_type& reference;
	typedef size_t		size_type;
	typedef ptrdiff_t	difference_type;

protected:
	typedef simple_alloc<value_type,alloc> data_allocator;
	iterator start;
	iterator finish;
	iterator end_of_storage;
	void insert_aux(iterator position, const T& x){//调用来自push_back,则position = end()
		if (finish != end_of_storage){//如果还有空余的空间
			construct(finish, *(finish - 1));
			++finish;
			T x_copy = x;
			copy_backward(position, finish - 2, finish - 1);
			*position = x_copy;		
		}else{//需要开辟新的空间
			const size_type old_size = size();
			const size_type len = old_size != 0 ? 2 * old_size : 1;//初始化/扩大 size
			
			iterator new_start = data_allocator::allocate(len);
			iterator new_finish = new_start;
			try{
				new_finish = uninitialized_copy(start, position, new_start);//将前半片旧数据拷贝到新开辟的空间内
				construct(new_finish, x);//末尾元素被构造成x
				++new_finish;
				new_finish = uninitialized_copy(position, finish, new_finish);//将后半片旧数据拷贝到新开辟的空间内
			}catch(...){//catch all the exceptions
				destroy(new_start, new_finish);
				data_allocator::deallocate(new_start, len);
				throw;
			}
			
			destroy(begin(),end());
			deallocate();//销毁原本的空间
			
			start = new_start;
			finish = new_finish;
			end_of_storage = new_start + len;
		}
	}
	void deallocate(){
		if (start)
			data_allocator::deallocate(start,end_of_storage - start);
	}
	void fill_initialize(size_type n, const T& value){
		start = allocate_and_fill(n,value);
		finish = start + n;
		end_of_storage = finish;
	}

public:
	iterator begin(){ return start; }
	const_iterator begin() const { return start; }
	iterator end() { return finish; }
	const_iterator end() const { return finish; }
	size_type size() const { return size_type(end() - begin()); }
	size_type capacity() const {
		return size_type(end_of_storage - begin());
	}
	bool empty() const { return begin() == end();}
	reference operator[](size_type n){ return *(begin() + n); }
	Vector():start(0),finish(0), end_of_storage(0){
		std::cout<<std::endl;
		LOG("Vector is contructed","",0);
	}
	~Vector(){
		LOG("Vector is destructing...","",0);
		destroy(start,finish);
		deallocate();
	}
	void pop_back(){
		LOG("pop_back...","",0);
		--finish;
		destroy(finish);
	}
	
	iterator erase(iterator first, iterator last){
		LOG("erase from...","first",*first);
		LOG("until...","last",*last);
		iterator i = copy(last, finish, first);//将后半片旧数据往前移
		destroy(i,finish);//销毁end()
		finish = finish - (last - first);//确定finish的新位置
		return first;
	}
	
	iterator erase(iterator position){
		LOG("erase","position",*position);
		if (position + 1 != end()){
			copy(position + 1, finish, position);//后续元素往前移动
		}
		--finish;//end()往前移，注意末尾是开区间，故销毁end()所在的元素
		destroy(finish);
		return position;
	}
	
	void clear(){
		LOG("clear","",0);
		erase(begin(),end());
	}
	void push_back(const T& x){
		LOG("push_back: ","value",x);
		if (finish != end_of_storage){
			construct(finish, x);
			++finish;
		}else
			insert_aux(end(), x);
	}


};

#endif