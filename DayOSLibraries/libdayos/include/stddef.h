#ifndef STDDEF_H
#define STDDEF_H

#include <stdint.h>

typedef __SIZE_TYPE__ size_t;
typedef __PTRDIFF_TYPE__ ptrdiff_t;

typedef long int ssize_t;

typedef uint32_t mode_t;
typedef uint32_t ino_t;
typedef uint32_t dev_t;
typedef uint32_t off_t;

#ifndef NULL
#define NULL 0x0
#endif

#define offsetof(type, member) ((size_t)&((type*) 0)->member)

#endif
