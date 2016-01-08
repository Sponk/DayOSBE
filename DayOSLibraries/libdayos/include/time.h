#ifndef __TIME_H
#define __TIME_H

#include <stddef.h>
#include <kernelconfig.h>

typedef long long time_t;
typedef time_t clock_t;

struct timespec
{
	time_t tv_sec;
	long tv_nsec;
};

struct tm
{
	int tm_sec;
	int tm_min;
	int tm_hour;
	int tm_mday;
	int tm_mon;
	int tm_year;
	int tm_wday;
	int tm_yday;
	int tm_isdst;
};

#ifdef __cplusplus
extern "C" {
#endif

clock_t clock();
time_t time(time_t* timer);
struct tm* gmtime(const time_t* timer);
struct tm* localtime(const time_t* timer);

size_t strftime(char* ptr, size_t maxsize, const char* format, const struct tm* timeptr);
time_t mktime(struct tm* timeptr);
double difftime(time_t end, time_t beginning);
char* ctime (const time_t* timer);

char* asctime(const struct tm* timeptr);

#ifdef __cplusplus
}
#endif

#endif