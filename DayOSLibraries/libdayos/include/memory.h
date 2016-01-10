#ifndef __MEMORY_H
#define __MEMORY_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void request_mem_region(const char* name, uintptr_t addr);

#ifdef __cplusplus
}
#endif
#endif