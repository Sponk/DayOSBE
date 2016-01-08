#include <time.h>
#include <syscall.h>

// FIXME: Implementation!
clock_t clock()
{
	return 0;
}

// FIXME: Implementation!
time_t time(time_t* timer)
{
	return *timer;
}

struct tm* gmtime(const time_t* timer)
{
	return NULL;
}

struct tm* localtime(const time_t* timer)
{
	return NULL;
}

size_t strftime(char* ptr, size_t maxsize, const char* format, const struct tm* timeptr)
{
	return 0;
}

time_t mktime(struct tm* timeptr)
{
	return 0;
}

double difftime(time_t end, time_t beginning)
{
	return 0;
}

char* ctime (const time_t* timer)
{
	return " ";
}

char* asctime(const struct tm* timeptr)
{
	return " ";
}
