#ifndef __ALGORITHM_H_
#define __ALGORITHM_H_


template <class InputIterator, class OutputIterator>
inline OutputIterator  copy(InputIterator first, InputIterator last, OutputIterator result){
	while (first != last){
		*result = *first;
		result++;
		first++;
	}
	return result;
}

template <class T> 
const T& max (const T& a, const T& b) {
  return (a < b) ? b : a;     // or: return comp(a,b)?b:a; for version (2)
}

template<class BidirectionalIterator1, class BidirectionalIterator2>
BidirectionalIterator2 copy_backward ( BidirectionalIterator1 first,
                                         BidirectionalIterator1 last,
                                         BidirectionalIterator2 result )
{
  while (last!=first) *(--result) = *(--last);
  return result;
}


#endif