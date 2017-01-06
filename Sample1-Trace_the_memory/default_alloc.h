#ifndef __DEFAULT_ALLOC_H_
#define __DEFAULT_ALLOC_H_


#include <new>		/* placement new */
#include <cstddef>	/* for ptrdiff_t, size_t */
#include <cstdlib>	/* exit() */
#include <climits>	/* UINT_MAX */
#include <iostream> /* cerr */


enum {__ALIGN = 8};	//小型区块的上调边界
enum {__MAX_BYTES = 128};	//小型区块的上限
enum {__NFREELISTS = __MAX_BYTES / __ALIGN};	//free_list 个数

template <bool threads,int inst>
class __default_alloc_template{

private:
	static size_t ROUND_UP(size_t bytes){
		LOG("ROUNDING UP...","",0);
		//~(__ALIGN - 1) == 0xfffffffffffffff8
		//将bytes上升到8的倍数
		return (((bytes) + __ALIGN - 1) & ~(__ALIGN - 1));
	}
	union obj {
		union obj* free_list_link;
		char client_data[1];
	};
	
	static obj* volatile free_list[__NFREELISTS];
	static size_t FREELIST_INDEX(size_t bytes){
		return (((bytes) + __ALIGN - 1) / __ALIGN - 1);
	}
	
	static void* refill(size_t n);
	static char* chunk_alloc(size_t size, int& nobjs);
	
	static char* start_free;	//内存池起始位置，只在chunk_alloc()中变化
	static char* end_free;		//内存池结束位置，只在chunk_alloc()中变化
	static size_t heap_size;
	
public:
	static void* allocate(size_t n){
		LOG("allocate from memory pool...","bytes",n);
		obj* volatile * my_free_list;
		obj* result;
		if (n > (size_t) __MAX_BYTES){//如果大于128bytes,则直接调用malloc,内存池中没那么大的chunk
			return malloc_alloc::allocate(n);
		}
		my_free_list = free_list + FREELIST_INDEX(n);//找到对应大小的freelist位置
		result = *my_free_list;
		if (result == 0){
			//没有可用的freelist，则从内存池填充
			void* r = refill(ROUND_UP(n));
			return r;
		}
		*my_free_list = result -> free_list_link;//将result从freelist中取出，返回result
		return result;
	}
	static void deallocate(void* p,size_t n){
		LOG("deallocate to memory pool...","bytes",n);
		obj* q = (obj*)p;
		obj* volatile *my_free_list;
		
		if (n > (size_t) __MAX_BYTES){//如果太大直接调用malloc去分配
			malloc_alloc::deallocate(p,n);
			return;
		}
		my_free_list = free_list + FREELIST_INDEX(n);
		
		q->free_list_link = *my_free_list;//将释放的内存块重新放到freelist中
		*my_free_list = q;
	}
	static void* reallocate(void* p, size_t old_sz, size_t new_sz);
};

template <bool threads, int inst>
void* __default_alloc_template<threads, inst>::refill(size_t n){
	int nobjs = 20;//一次分配20个区块
	char* chunk = chunk_alloc(n,nobjs);//pass by reference
	obj* volatile * my_free_list;
	obj* result;
	obj* current_obj, *next_obj;
	int i;
	LOG("refill from memory pool...","bytes",n);
	LOG("refill from memory pool...","chunks",nobjs);
	if (1 == nobjs){//如果只返回了一个区块，则直接给客户使用即可
		return chunk;
	}
	my_free_list = free_list + FREELIST_INDEX(n);
	result = (obj*)chunk;
	*my_free_list = next_obj = (obj*)(chunk + n);
	
	for (i = 1;;i++){//将所有申请来的区块都链接到freelist上
		current_obj = next_obj;
		next_obj = (obj*)((char*)next_obj + n);
		if (nobjs - 1 == i){
			current_obj -> free_list_link = 0;
			break;
		}else{
			current_obj -> free_list_link = next_obj;
		}
	}
	return result;
}

template <bool threads, int inst>
char* __default_alloc_template<threads,inst>::start_free = 0;

template <bool threads, int inst>
char* __default_alloc_template<threads,inst>::end_free = 0;

template <bool threads, int inst>
size_t __default_alloc_template<threads,inst>::heap_size = 0;

template <bool threads, int inst>
typename __default_alloc_template<threads, inst>::obj* volatile
__default_alloc_template<threads, inst>::free_list[__NFREELISTS] = {
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};

template <bool threads, int inst>
char* __default_alloc_template<threads, inst>::chunk_alloc(size_t size, int& nobjs){
	char* result;
	size_t total_bytes = size * nobjs;
	size_t bytes_left = end_free - start_free;//内存池剩余空间
	
	if (bytes_left >= total_bytes){//如果内存池内水量充足
		result = start_free;
		start_free += total_bytes;
		return result;
	}else if (bytes_left >= size){//如果内存池内至少还有一个区块可提供
		nobjs = bytes_left / size;
		total_bytes = size * nobjs;
		result = start_free;
		start_free += total_bytes;
		return result;
	}else{//如果连一个区块也提供不了
		size_t bytes_to_get = 2 * total_bytes + ROUND_UP(heap_size >> 4);//两倍的当前所需量 + 附加值
		if (bytes_left > 0){//如果还有剩余的内存，尽量利用，将其加入free_list
			obj* volatile * my_free_list = free_list + FREELIST_INDEX(bytes_left);
			((obj*)start_free) -> free_list_link = *my_free_list;
			*my_free_list = (obj*)start_free;
		}
		start_free = (char*)malloc(bytes_to_get);
		if (0 == start_free){//若heap空间不足，malloc申请失败
			int i;
			obj* volatile * my_free_list, *p;
			for (i = size; i <= __MAX_BYTES; i += __ALIGN){
				my_free_list = free_list + FREELIST_INDEX(i);
				p = *my_free_list;
				if (0 != p){
					*my_free_list = p->free_list_link;
					start_free = (char*)p;
					end_free = start_free + i;
					return chunk_alloc(size,nobjs);//递归调用申请内存
				}
			}
			end_free = 0;
			//转而调用上层内存配置器，调用oom机制，会抛出异常
			start_free = (char*)malloc_alloc::allocate(bytes_to_get);
		}
		heap_size += bytes_to_get;
		end_free = start_free + bytes_to_get;
		return chunk_alloc(size,nobjs);//递归调用申请内存
	}
}


# ifdef __USE_MALLOC
typedef __malloc_alloc_template<0> malloc_alloc
typedef malloc_alloc alloc
# else
//typedef __default_alloc_template<__NODE_ALLOCATOR_THREADS,0> alloc;
typedef __default_alloc_template<0,0> alloc;
# endif



#endif























