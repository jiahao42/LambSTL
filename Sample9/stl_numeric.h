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

template <class InputIterator, class OutputIterator, class T>
OutputIterator __adjacent_difference(InputIterator first, InputIterator last, OutputIterator result, T*) {
	T value = *first;
	while (++first != last) {
		T tmp = *first;
		*++result = tmp - value; /* The latter value - the former value */
		value = tmp;
	}
	return ++result;
}

template <class InputIterator, class OutputIterator>
OutputIterator adjacent_difference(InputIterator first, InputIterator last, OutputIterator result) {
	if (first == last)	return result;
	*result = *first;
	return __adjacent_difference(first, last, result, value_type(first));
}



template <class InputIterator, class OutputIterator, class T, class BinaryOperation>
OutputIterator __adjacent_difference(InputIterator first, InputIterator last, OutputIterator result, T*, BinaryOperation binary_op) {
	T value = *first;
	while (++first != last) {
		T tmp = *first;
		*++result = binary_op(tmp, value);
		value = tmp;
	}
	return ++result;
}

template <class InputIterator, class OutputIterator, class BinaryOperation>
OutputIterator adjacent_difference(InputIterator first, InputIterator last, OutputIterator result, BinaryOperation binary_op) {
	if (first == last)
		return result;
	*result = *first;
	return __adjacent_difference(first, last, result, value_type(first), binary_op);
}






#endif