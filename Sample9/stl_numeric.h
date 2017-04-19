#ifndef __LAMB_STL_INTERNAL_NUMERIC_H_
#define __LAMB_STL_INTERNAL_NUMERIC_H_

template <class InputIterator, class T>
T accumulate(InputIterator first, InputIterator last, T init) {
	for ( ; first != last; ++first)
		init = init + *first;
	return init;
}

template <class InputIterator, class T, class BinaryOperation> 
T accumulate (InputIterator first, InputIterator last, T init, BinaryOperation binary_op) {
	for ( ; first != last; ++first)
		init = binary_op(init, *first);
	return init;
}





#endif