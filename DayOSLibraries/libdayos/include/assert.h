#ifndef __ASSERT_H
#define __ASSERT_H

#define __symbol2value( x ) #x
#define __symbol2string( x ) __symbol2value( x )

#define assert(expression) if(!(expression)) assert_func("Assertion failed: " \
						"(" #expression ")" \
						", in file " __FILE__ \
						" at line " __symbol2string(__LINE__))

#ifdef __cplusplus
extern "C" {
#endif

void assert_func(const char* msg);

#ifdef __cplusplus
}
#endif

#endif