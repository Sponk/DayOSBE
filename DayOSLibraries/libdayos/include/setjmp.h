#ifndef SETJMP_H
#define SETJMP_H

#include <stdint.h>
#include <stddef.h>

typedef unsigned long jmp_buf;

void longjmp(jmp_buf env, int val);
int setjmp(jmp_buf env);

#define setjmp __builtin_setjmp
#define longjmp __builtin_longjmp

#endif
