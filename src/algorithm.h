#ifndef ALGORITHM_H_
#define ALGORITHM_H_


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
BidirectionalIterator2 copy_backward ( BidirectionalIterator1 first, BidirectionalIterator1 last, BidirectionalIterator2 result )
{
  while (last!=first) *(--result) = *(--last);
  return result;
}

template< class ForwardIt, class T >
void fill(ForwardIt first, ForwardIt last, const T& value)
{
    for (; first != last; ++first) {//传入首尾迭代器
        *first = value;
    }
}

template <class OutputIterator, class Size, class T>
OutputIterator fill_n (OutputIterator first, Size n, const T& val)
{
  while (n > 0) {//传入首迭代器与迭代器个数
    *first = val;
    ++first; --n;
  }
  return first;     // since C++11
}

template <class InputIterator, class Size>
void distance(InputIterator first, InputIterator last, Size& size){
	while(first != last){
		size++;
		first = ++first;
	}
}

#endif