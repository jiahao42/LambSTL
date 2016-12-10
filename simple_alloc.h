#ifndef __SIMPLE_ALLOC_H_
#define __SIMPLE_ALLOC_H_

#include "malloc_alloc.h"
#include "default_alloc.h"
//#include "uninitialized.h"

template <class T, class Alloc>
class simple_alloc{

public:
	static T* allocate(size_t n){
		return 0 == n ? 0 : (T*)Alloc::allocate(n * sizeof(T));
	}

	static T* allocate(void){
		return (T*)Alloc::allocate(sizeof(T));
	}
	
	static void deallocate(T* p, size_t n){
		if (0 != n)
			Alloc::deallocate(p, n * sizeof (T));
	}
	
	static void deallocate(T *p){
		Alloc::deallocate(p,sizeof(T));
	}
};

#endif

