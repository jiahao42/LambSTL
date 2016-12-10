#ifndef __TYPE_TRAITS_H_
#define __TYPE_TRAITS_H_

template <class type>
struct __type_traits{
	typedef __true_type 	this_dummy_member_must_be_first;
	typedef __false_type	has_trivial_default_constructor;
	typedef __false_type	has_trivial_copy_constructor;
	typedef __false_type	has_trivial_assignment_operator;
	typedef __false_type	has_trivial_destructor;
	typedef __false_type	is_POD_type;
}


#endif

