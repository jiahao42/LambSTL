#ifndef __LAMB_STL_INTERNAL_TYPE_TRAITS_H_
#define __LAMB_STL_INTERNAL_TYPE_TRAITS_H_

struct __true_type{};
struct __false_type{};
/*
下列是最基础的traits，接受任何型别的参数，并将各属性都设置成__false_type
__true_type将在相应的特化版本中给出
*/
template <class type>
struct __type_traits{
	typedef __true_type 	this_dummy_member_must_be_first;
	typedef __false_type	has_trivial_default_constructor;
	typedef __false_type	has_trivial_copy_constructor;
	typedef __false_type	has_trivial_assignment_operator;
	typedef __false_type	has_trivial_destructor;
	typedef __false_type	is_POD_type;
};


/*
特化版本之一 针对int
*/
//__STL_TEMPLATE_NULL	
template<> struct __type_traits<int>{
	typedef __true_type 	this_dummy_member_must_be_first;
	typedef __true_type	has_trivial_default_constructor;
	typedef __true_type	has_trivial_copy_constructor;
	typedef __true_type	has_trivial_assignment_operator;
	typedef __true_type	has_trivial_destructor;
	typedef __true_type	is_POD_type;
};


#endif

