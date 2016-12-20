#include "vector.h"


/*
template <class T, class Alloc>
void Vector<T,Alloc>::insert_aux (iterator position, const T& x){
	if (finish != end_of_storage){
		construct(finish, *(finish - 1));
		++finish;
		T x_copy = x;
		copy_backward(position, finish - 2, finish - 1);
		*position = x_copy;		
	}else{
		const size_type old_size = size();
		const size_type len = old_size != 0 ? 2 * old_size : 1;
		
		iterator new_start = data_allocator::allocate(len);
		iterator new_finish = new_start;
		try{
			new_finish = uninitialized_copy(start, position, new_start);
			construct(finish, x);
			++new_finish;
			new_finish = uninitialized_copy(position, finish, new_finish);
		}catch(...){//catch all the exceptions
			destroy(new_start, new_finish);
			data_allocator::deallocate(new_start, len);
			throw;
		}
		
		destroy(begin(),end());
		deallocate();
		
		start = new_start;
		finish = new_finish;
		end_of_storage = new_start + len;
	}
}
*/

