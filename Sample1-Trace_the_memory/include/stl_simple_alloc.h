#ifndef __LAMB_STL_SIMPLE_ALLOC_H_
#define __LAMB_STL_SIMPLE_ALLOC_H_

#include "stl_config.h"
#include "stl_malloc_alloc.h"
#include "stl_default_alloc.h"
//#include "uninitialized.h"


template <class T, class Alloc>
class simple_alloc{

public:
	static T* allocate(size_t n){
		LOG("allocating memory...","size",n * sizeof(T));
		return 0 == n ? 0 : (T*)Alloc::allocate(n * sizeof(T));
	}

	static T* allocate(void){
		LOG("allocating memory...","size",sizeof(T));
		return (T*)Alloc::allocate(sizeof(T));
	}
	
	static void deallocate(T* p, size_t n){
		LOG("deallocate memory...","size",n * sizeof(T));
		if (0 != n)
			Alloc::deallocate(p, n * sizeof (T));
	}
	
	static void deallocate(T *p){
		LOG("deallocate memory...","size",sizeof(T));
		Alloc::deallocate(p,sizeof(T));
	}
};

#endif

