#ifndef SYSCALL_H
#define SYSCALL_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

// syscall1 takes one argument for the kernel, syscall2 would take two.
int syscall1(int syscall, int ebx);
int syscall2(int syscall, int ebx, int ecx);

#ifdef __cplusplus
}
#endif
	
#endif
