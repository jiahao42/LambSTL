#ifndef __ITERATOR_TRAITS_H_
#define __ITERATOR_TRAITS_H_


struct input_iterator_tag{};
struct output_iterator_tag{};
struct forward_iterator_tag : public input_iterator_tag{};
struct bidirectional_iterator_tag : public forward_iterator_tag{};
struct random_access_iterator_tag : public bidirectional_iterator_tag{};



template <class I>
struct iterator_traits{
	typedef typename I::iterator_category 	iterator_category;
	typedef typename I::value_type			value_type;
	typedef typename I::difference_type 	difference_type;
	typedef typename I::pointer				pointer;
	typedef typename I::reference			reference;
};


/* 原生类型的特化 */
template <class T>
struct iterator_traits<T*>{//原生指针，必定是random access
	typedef  random_access_iterator_tag 	iterator_category;
	typedef  T								value_type;
	typedef  ptrdiff_t 						difference_type;
	typedef  T*								pointer;
	typedef  T&								reference;
};

/* const 原生类型的特化 */
template <class T>
struct iterator_traits<const T*>{//原生指针，必定是random access
	typedef  random_access_iterator_tag 	iterator_category;
	typedef  T								value_type;
	typedef  ptrdiff_t 						difference_type;
	typedef  T*								pointer;
	typedef  T&								reference;
};

/*
取得value_type

为什么返回指针
For an arbitrary type, T, we don't know how to construct it, or if it's copyable or movable. So passing a value_type directly could be impossible and could incur an entirely unwanted copy with side-effects that could be unelidable. But we do know for sure that we can construct a T* from 0. So using a zero-initialized pointer to value_type is a handy hack in this situation.
*/
template <class Iterator>
inline typename iterator_traits<Iterator>::value_type* value_type(const Iterator&){
	return static_cast<typename iterator_traits<Iterator>::value_type*>(0);
}

#endif