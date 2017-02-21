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









# endif