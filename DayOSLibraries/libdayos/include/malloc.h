#ifndef __MALLOC_H
#define __MALLOC_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void* malloc(size_t size);
void free(void* p);
void* realloc(void* p, size_t sz);
void* calloc(size_t num, size_t bytes);

#ifdef __cplusplus
}
#endif

#endif