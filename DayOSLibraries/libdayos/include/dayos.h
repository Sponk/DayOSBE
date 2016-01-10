#ifndef DAYOS_H
#define DAYOS_H

#include "message.h"
#include "service.h"
#include "interrupts.h"
#include "vfs.h"
#include "sleep.h"

#ifdef __cplusplus
extern "C" {
#endif

int debug_printf(const char* fmt, ...);
void debug_putch(int c);

#ifdef __cplusplus
}
#endif

#endif
