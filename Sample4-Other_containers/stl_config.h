#ifndef __STL_CONFIG_H_
#define __STL_CONFIG_H_


#ifdef _PTHREADS
#	define __STL_PTHREADS
#endif

# if defined(__sgi) && !defined(__GNUC__)
#	if !defined(_BOOL)
#		define __STL_NEED_BOOL
#	endif
#	if !defined(_TYPENAME_IS_KEYWORD)
#		define __STL_NEED_TYPENAME
#	endif
#	ifdef _PARTIAL_SPECIALIZATION_OF_CLASS_TEMPLATES
#		define __STL_CLASS_PARTIAL_SPECIALIZATION
#	endif
#	ifdef _MEMBER_TEMPLATES
#		define __STL_MEMBER_TEMPLATES
#	endif
#	ifdef !defined(_EXPLICIT_IS_KEYWORD)
#		define __STL_NEED_EXPLICIT
#	endif
#	ifdef __EXCEPTIONS
#		define __STL_USE_EXCEPTIONS
#	endif
#	if (_COMPLIER_VERSION >= 721) && defined(_NAMESPACES)
#		define __STL_USE_NAMESPACES
#	endif
#	if !defined(_NOTHREADS)	&&	!defined(__STL_PTHREADS)
#		define __STL_SGI_THREADS
#	endif
# endif


# ifdef __GNUC__
#   include <_G_config.h>
#   if __GNUC__ < 2 || (__GNUC__ == 2 && __GNUC_MINOR__ < 8)
#     define __STL_STATIC_TEMPLATE_MEMBER_BUG
#     define __STL_NEED_TYPENAME
#     define __STL_NEED_EXPLICIT
#   else
#     define __STL_CLASS_PARTIAL_SPECIALIZATION
#     define __STL_FUNCTION_TMPL_PARTIAL_ORDER
#     define __STL_EXPLICIT_FUNCTION_TMPL_ARGS
#     define __STL_MEMBER_TEMPLATES
#   endif

# 	if !defined(_NOTHREADS) && __GLIBC__ >= 2 && defined(_G_USING_THUNKS)
#		define __STL_PTHREADS
# 	endif
# 	ifdef __EXCEPTIONS
#		define __STL_USE_EXCEPTIONS
# 	endif
# endif

# if defined(__SUNPRO_CC)
# 	define __STL_NEED_BOOL
#	define __STL_NEED_TYPENAME
#	define __STL_NEED_EXPLICIT
#	define __STL_USE_EXCEPTIONS
# endif

# if defined(__COMO__)
#	define __STL_MEMBER_TEMPLATES
#	define __STL_CLASS_PARTIAL_SPECIALIZATION
# 	define __STL_USE_EXCEPTIONS
#	define __STL_USE_NAMESPACES
# endif

//VC6的版本号是1200
# if defined(_MSC_VER)
# 	if _MSC_VER > 1000
#		include <yvals.h>
#	else
#		define __STL_NEED_BOOL
#	endif
#	define __STL_NO_DRAND48
#	define __STL_NEED_TYPENAME
#	if _MSC_VER < 1100
#		define __STL_NEED_EXPLICIT
#	endif
#	define __STL_NON_TYPE_TMPL_PARAM_BUG
#	define __SGI_STL_NO_ARROW_OPERATOR
#	ifdef _CPPUNWIND
#		define __STL_USE_EXCEPTIONS
#	endif
#	ifdef _MT
#		define __STL_WIN32THREADS
#	endif
# endif

//此处省略了Borland C++builder的宏定义

# if defined(__STL_NEED_BOOL)
	typedef int bool;
# define true 1
# define false 0
#endif

# ifdef __STL_NEED_TYPENAME
#	define typename	class
# endif

# ifdef __STL_NEED_EXPLICIT
#	define explicit
# endif

# ifdef __STL_EXPLICIT_FUNCTION_TMPL_ARGS
#	define __STL_NULL_TMPL_ARGS <>
# else
#	define __STL_NULL_TMPL_ARGS
# endif

# ifdef __STL_CLASS_PARTIAL_SPECIALIZATION
#	define __STL_TEMPLATE_NULL template<>
# else
#	define __STL_TEMPLATE_NULL
# endif

# if defined (__STL_USE_NAMESPACES) && !defined(__STL_NO_NAMESPACES)
#	define __STD std
#	define __STL_BEGIN_NAMESPACE namespace std{
#	define __STL_END_NAMESPACE }
#	define __STL_USE_NAMESPACE_FOR_RELOPS
#	define __STL_BEGIN_RELOPS_NAMESPACE namespace std {
#	define __STL_END_RELOPS_NAMESPACE }
#	define __STD_RELOPS std
# else
#	define __STD
#	define __STL_BEGIN_NAMESPACE
#	define __STL_END_NAMESPACE
#	define __STL_USE_NAMESPACE_FOR_RELOPS
#	define __STL_BEGIN_RELOPS_NAMESPACE
#	define __STL_END_RELOPS_NAMESPACE
#	define __STD_RELOPS
# endif


# ifdef __STL_USE_EXCEPTIONS
#   define __STL_TRY try
#   define __STL_CATCH_ALL catch(...)
#   define __STL_THROW(x) throw x
#   define __STL_RETHROW throw
#   define __STL_NOTHROW throw()
#   define __STL_UNWIND(action) catch(...) { action; throw; }
# else
#   define __STL_TRY
#   define __STL_CATCH_ALL if (false)
#   define __STL_THROW(x)
#   define __STL_RETHROW
#   define __STL_NOTHROW
#   define __STL_UNWIND(action)
# endif

# ifdef __STL_ASSERTIONS
#	include <stdio.h>
#	define __stl_assert(expr) \
		if (!(expr)) { fprintf(stderr, "%s:%d STL assertion failure: %s\n", __FILE__, __LINE__, # expr); abort(); }
# else
#	define __stl_assert(expr)
# endif

#define __SHOW_LOGS

#ifdef __SHOW_LOGS
#define LOG(operation, parameter, value) \
	do { \
		if (parameter == ""){ \
			fprintf(stderr,"%s:%d: %s\n",__FILE__,__LINE__,operation);\
		}else { \
			fprintf(stderr,"%s:%d: %s, [%s]: %d\n",__FILE__,__LINE__,operation,parameter,static_cast<int>(value));\
		} \
	} while(0)
#else
#define LOG(operation, parameter, value) do {} while(0)
#endif

#endif


