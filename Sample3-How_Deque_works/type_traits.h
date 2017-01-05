#ifndef __TYPE_TRAITS_H_
#define __TYPE_TRAITS_H_

/*
一个class什么时候应该有自己的
non-trivial default constructor,
non-trivial copy constructor,
non-trivial assignment operator,
non-trivial destructor
### 准则：
如果class内含指针成员，并且对它进行动态内存配置，那么这个class就需要实现出自己的non-trivial-xxx
*/



/*
下列是最基础的traits，接受任何型别的参数，并将各属性都设置成__false_type
__true_type将在相应的特化版本中给出
值得注意的是，如果写了自定义的class，意味着标准库中没有相应特化的__type_traits，所有的属性都被定义成__false_type
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
	typedef __true_type		has_trivial_default_constructor;
	typedef __true_type		has_trivial_copy_constructor;
	typedef __true_type		has_trivial_assignment_operator;
	typedef __true_type		has_trivial_destructor;
	typedef __true_type		is_POD_type;
};


#endif

