#ifndef __MALLOC_ALLOC_H_
#define __MALLOC_ALLOC_H_

#include <new>		/* placement new */
#include <cstddef>	/* for ptrdiff_t, size_t */
#include <cstdlib>	/* exit() */
#include <climits>	/* UINT_MAX */
#include <iostream> /* cerr */
#include <cstdio>   /* fprintf */


#if 0
#	include <new>
#	define __THROW_BAD_ALLOC throw bad_alloc
#elif	!defined(__THROW_BAD_ALLOC)
#	include <iostream>
#	define __THROW_BAD_ALLOC std::cerr<<"out of memory"<<std::endl;	exit(1);
#endif

/*
第一级配置器，使用malloc(),free(),realloc()来配置内存
如果配置失败，则调用private的oom_malloc(),oom_realloc()来反复配置内存
要注意的是，内存分配失败的处理例程要有客户自行设计并设置
*/

template <int inst>
class __malloc_alloc_template{
private:
	static void *oom_malloc(size_t);
	static void *oom_realloc(void*, size_t);
	static void (* __malloc_alloc_oom_handler)();

public:
	static void* allocate(size_t n){
		void* result = malloc(n);
		if (0 == result)	result = oom_malloc(n);
		PRINT_LINE();
		std::cout<<"allocate "<<n<<" bytes memory using malloc"<<std::endl; 
		return result;
	}
	
	static void deallocate(void* p, size_t){
		PRINT_LINE();
		std::cout<<"deallocate memory"<<std::endl;
		free(p);
	}
	
	static void* reallocate(void* p, size_t old_sz, size_t new_sz){
		void* result = realloc(p, new_sz);
		PRINT_LINE();
		std::cout<<"realloc memory from "<<old_sz<<" size to "<<new_sz<<std::endl;
		if (0 == result)	result = oom_realloc(p, new_sz);
		return result;
	}
	
	static void (* set_malloc_handler(void(*f)()))(){
		void (* old)() = __malloc_alloc_oom_handler;
		__malloc_alloc_oom_handler = f;
		return old;
	}
};

template<int inst>
void (* __malloc_alloc_template<inst>::__malloc_alloc_oom_handler)() = 0;

template<int inst>
void* __malloc_alloc_template<inst>::oom_malloc(size_t n){
	void (* my_malloc_handler)();
	void *result;
	
	for(;;){
		my_malloc_handler = __malloc_alloc_oom_handler;
		if (0 == my_malloc_handler)	{ __THROW_BAD_ALLOC; }
		(*my_malloc_handler)();
		result = malloc(n);
		if (result)	return result;
	}
}

template <int inst>
void* __malloc_alloc_template<inst>::oom_realloc(void* p, size_t n){
	void (* my_malloc_handler)();
	void* result;
	
	for(;;){
		my_malloc_handler = __malloc_alloc_oom_handler;
		if (0 == my_malloc_handler)	{__THROW_BAD_ALLOC;}
		(*my_malloc_handler)();
		result = realloc(p,n);
		if (result)	return result;
	}
}

typedef __malloc_alloc_template<0> malloc_alloc;

#endif











