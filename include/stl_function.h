# ifndef __LAMB_STL_INTERNAL_FUNCTION_H_
# define __LAMB_STL_INTERNAL_FUNCTION_H_


template <class Arg, class Result>
struct unary_function {
	typedef Arg argument_type;
	typedef Result result_type;
};

template <class Arg1, class Arg2, class Result>
struct binary_function {
	typedef Arg1 first_argument_type;
	typedef Arg2 second_argument_type;
	typedef Result result_type;
};

//Arithmetic function object
template <class T>
struct plus : public binary_function<T, T, T> {
	T operator() (const T& x, const T& y) const { return x + y; }
};

template <class T>
struct minus : public binary_function<T, T, T> {
	T operator() (const T& x, const T& y) const { return x - y; }
};

template <class T>
struct multiplies : public binary_function<T, T, T> {
	T operator() (const T& x, const T& y) const { return x * y; }
};

template <class T>
struct divides : public binary_function<T, T, T> {
	T operator() (const T& x, const T& y) const { return x / y; }
};

template <class T>
struct modulus : public binary_function<T, T, T> {
	T operator() (const T& x, const T& y) const { return x % y; }
};

template <class T>
struct negate : public unary_function<T, T> {
	T operator() (const T& x) const { return -x; }
};

//Relation function object
template <class T>
struct equal_to : public binary_function<T, T, bool> {
	bool operator() (const T& x, const T& y) const { return x == y; }
};

template <class T>
struct not_equal_to : public binary_function<T, T, bool> {
	bool operator() (const T& x, const T& y) const { return x != y; }
};

template <class T>
struct greater : public binary_function<T, T, bool> {
	bool operator() (const T& x, const T& y) const { return x > y; }
};

template <class T>
struct less : public binary_function<T, T, bool> {
	bool operator() (const T& x, const T& y) const { return x < y; }
};

template <class T>
struct greater_equal : public binary_function<T, T, bool> {
	bool operator() (const T& x, const T& y) const { return x >= y; }
};

template <class T>
struct less_equal : public binary_function<T, T, bool> {
	bool operator() (const T& x, const T& y) const { return x <= y; }
};

//Logical function object
template <class T>
struct logical_and : public binary_function<T, T, bool> {
	bool operator() (const T& x, const T& y) const { return x && y; }
};

template <class T>
struct logical_or : public binary_function<T, T, bool> {
	bool operator() (const T& x, const T& y) const { return x || y; }
};

template <class T>
struct logical_not : public unary_function<T, bool> {
	bool operator() (const T& x) const { return !x; }
};

# endif