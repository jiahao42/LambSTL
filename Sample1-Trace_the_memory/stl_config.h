#ifndef __STL_CONFIG_H_
#define __STL_CONFIG_H_

struct __true_type{};
struct __false_type{};


#define __STL_TEMPLATE_NULL template<>

#define __SHOW_LOGS

#ifdef __SHOW_LOGS
#define PRINT_LINE() fprintf(stderr,"%s:%d : ",__FILE__,__LINE__);
#else
#define PRINT_LINE()
#endif


#endif


