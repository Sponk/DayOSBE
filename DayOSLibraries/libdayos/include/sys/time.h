#ifndef __SYS_TIME_H
#define __SYS_TIME_H

#include <stdint.h>
#include <stddef.h>
#include <sys/types.h>

struct timeval
{
	time_t tv_sec;
	suseconds_t tv_usec;
};

#endif