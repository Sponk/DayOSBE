#ifndef DAYOS_H
#define DAYOS_H

#include "message.h"
#include "service.h"
#include "interrupts.h"
#include "vfs.h"
#include "sleep.h"
#include "buffer.h"

#ifdef __cplusplus
extern "C" {
#endif

int debug_printf(const char* fmt, ...);
void debug_putch(int c);
int execute_program(const char* path, int argc, char* argv[]);

#ifdef __cplusplus
}
#endif

#endif
