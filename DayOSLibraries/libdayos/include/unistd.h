#ifndef __UNISTD_H
#define __UNISTD_H

#include "stdint.h"
#include "stddef.h"
#include "fcntl.h"
#include "message.h"

#define STDIN_FILENO 0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

#define F_OK SIGNAL_OK

#ifdef __cplusplus
extern "C" {
#endif

extern char* optarg;
extern int optind, opterr, optopt;
int getopt(int argc, char* argv[], const char* opts);

#ifdef __cplusplus
}
#endif

#endif
