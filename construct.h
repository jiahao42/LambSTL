#ifndef __CONSTRUCT_H_
#define __CONSTRUCT_H_

#include <new>

template <class T1, class T2>
inline void construct(T1* p, const T2& value){
	new (p) T1 (value);
}

template <class T>
inline void destroy(T* pointer){
	pointer->~T();
}

template <class ForwardIterator>
inline void destroy(ForwardIterator first, ForwardIterator last){
	__destory(first, last, value_type(first));
}

template <class ForwardIterator, class T>
inline void __destory(ForwardIterator first, ForwardIterator last, T*){
	typedef typename  <T>::has_trivial_destructor trivial_destructor;
	__destory_aux(first, last, trivial_destructor());
}

template <class ForwardIterator>
inline void __destory_aux(ForwardIterator first, ForwardIterator last, __false_type){
	for(; first < last; ++first){
		destroy(&*first);
	}
}

template <class ForwardIterator>
inline void __destory_aux(ForwardIterator, ForwardIterator, __true_type){}


//以下为destory()针对迭代器为char*与wchar_t*的特化版
inline void destroy(char*, char*){}
inline void destroy(wchar_t*, wchar_t*){}

#endif





