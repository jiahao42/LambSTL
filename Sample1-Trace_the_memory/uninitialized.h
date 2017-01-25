#ifndef UNINITIALIZED_H_
#define UNINITIALIZED_H_
#include "iterator.h"
#include <iostream>



/* start of uninitialized_fill_n */
/*
parameters：
	first:迭代器first指向欲初始化空间的起始处
	n:表示欲初始化空间的大小
	x:表示要初始化成的初值
*/

//如果不是POD则依次调用构造函数
template <class ForwardIterator, class Size, class T>
ForwardIterator __uninitialized_fill_n_aux(ForwardIterator first, Size n, const T& x, __false_type){
	LOG("__uninitialized_fill_n_aux: not POD, filling...","",0);
	ForwardIterator cur = first;
	for (; n > 0; --n, ++cur)
		construct(&*cur,x);
	return cur;
}


template <class ForwardIterator, class Size, class T, class T1>
inline ForwardIterator __uninitialized_fill_n(ForwardIterator first, Size n, const T& x, T1 *){
	//POD = Plain Old Data，scalar types 或者 传统C struct
	//POD比如拥有trivial ctor/dtor/copy/assignment函数
	LOG("__uninitialized_fill_n: isPOD()...","",0);
	typedef typename __type_traits<T1>::is_POD_type is_POD;
	return __uninitialized_fill_n_aux(first, n, x, is_POD());
}


template <class ForwardIterator, class Size, class T>
inline ForwardIterator uninitialized_fill_n(ForwardIterator first, Size n, const T& x){
	LOG("uninitialized_fill_n: extracting value_type...","",0);
	return __uninitialized_fill_n(first, n, x, value_type(first));//使用value_type提取出first的type
}

template <class ForwardIterator, class Size, class T>
inline ForwardIterator __uninitialized_fill_n_aux(ForwardIterator first, Size n, const T& x, __true_type){
	LOG("__uninitialized_fill_n_aux: is POD, filling...","",0);
	return fill_n(first, n, x);//调用高阶函数
}



/* end of uninitialized_fill_n */


//假装一个copy函数
template <class InputIterator, class OutputIterator>
inline OutputIterator  copy(InputIterator first, InputIterator last, OutputIterator result){
	LOG("copying...","",0);
	while (first != last){
		*result = *first;
		result++;
		first++;
	}
	return result;
}


/* start of uninitialized_copy */
/*
parameters：
	first:指向输入端的起始位置
	last:指向输入端的结束位置
	result:指向输出端
*/
template <class InputIterator, class ForwardIterator>
ForwardIterator __uninitialized_copy_aux(InputIterator first, InputIterator last, ForwardIterator result, __false_type){
	ForwardIterator cur = result;
	LOG("__uninitialized_copy_aux: copying with constructor...","",0);
	for ( ; first != last; ++first, ++cur)
		construct(&*cur,*first);
	return cur;
}

template <class InputIterator, class ForwardIterator>
inline ForwardIterator __uninitialized_copy_aux(InputIterator first, InputIterator last, ForwardIterator result, __true_type){
	LOG("__uninitialized_copy_aux: copying without constructor...","",0);
	return copy(first,last,result);//高阶函数
}

template <class InputIterator, class ForwardIterator, class T>
inline ForwardIterator __uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result, T*){
	typedef typename __type_traits<T>::is_POD_type is_POD;
	LOG("__uninitialized_copy: is POD()...","",0);
	return __uninitialized_copy_aux(first, last, result, is_POD());//is POD?
}

template <class InputIterator, class ForwardIterator>
inline ForwardIterator uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result){
	LOG("uninitialized_copy: extracting value_type...","",0);
	return __uninitialized_copy(first, last, result, value_type(result));//先取出type
}





/* end of uninitialized_copy */


/* start of uninitialized_fill */
/*
parameters：
	first:指向欲初始化空间的起始处
	last:指向欲初始化空间的结束处
	x:表示初值
*/
template <class ForwardIterator, class T>
inline void __uninitialized_fill_aux(ForwardIterator first, ForwardIterator last, const T& x, __true_type){
	LOG("__uninitialized_fill_aux: filling without constructor...",NULL,0);
	fill(first, last, x);
}

template <class ForwardIterator, class T>
void __uninitialized_fill_aux(ForwardIterator first, ForwardIterator last, const T& x,__false_type){
	ForwardIterator cur = first;
	LOG("__uninitialized_fill_aux: filling with constructor...",NULL,0);
	for ( ; cur != last; ++cur)
		construct(&*cur,x);
}


template <class ForwardIterator, class T, class T1>
inline void __uninitialized_fill(ForwardIterator first, ForwardIterator last, const T& x, T1*){
	typedef typename __type_traits<T1>::is_POD_type is_POD;
	LOG("__uninitialized_fill: isPOD()...",NULL,0);
	__uninitialized_fill_aux(first, last, x, is_POD());
}


template <class ForwardIterator, class T>
inline void uninitialized_fill(ForwardIterator first, ForwardIterator last, const T& x){
	LOG("uninitialized_fill: extracting value_type...",NULL,0);
	__uninitialized_fill(first,last,x,value_type(first));
}



/* end of uninitialized_fill */




#endif

