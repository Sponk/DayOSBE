#ifndef UTIME_H
#define UTIME_H

#include <stddef.h>

struct utimbuf
{
	time_t actime;
	time_t modtime;
};

#ifdef __cplusplus
extern "C" {
#endif

int utime(const char* filename, const struct utimbuf* times);
#ifdef __cplusplus
}
#endif

#endif