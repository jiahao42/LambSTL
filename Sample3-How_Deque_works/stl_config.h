#ifndef __STL_CONFIG_H_
#define __STL_CONFIG_H_

struct __true_type{};
struct __false_type{};


#define __STL_TEMPLATE_NULL template<>

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

#define __SHOW_LOGS

#ifdef __SHOW_LOGS
#define LOG(operation, parameter, value) \
	do { \
		if (parameter == ""){ \
			fprintf(stderr,"%s:%d: %s\n",__FILE__,__LINE__,operation);\
		}else { \
			fprintf(stderr,"%s:%d: %s, [%s]: %d\n",__FILE__,__LINE__,operation,parameter,(int)value);\
		} \
	} while(0)
#else
#define LOG(operation, parameter, value) do {} while(0)
#endif

#endif


