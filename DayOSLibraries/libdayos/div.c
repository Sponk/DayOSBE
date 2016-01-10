#include <stdlib.h>

div_t div(int numer, int denom)
{
	div_t result;
	result.quot = numer / denom;
	result.rem = numer % denom;
	return result;
}

ldiv_t ldiv(long int numer, long int denom)
{
	ldiv_t result;
	result.quot = numer / denom;
	result.rem = numer % denom;
	return result;
}

int abs(int n)
{
	if(n < 0)
		return -n;
	
	return n;
}

long labs(long n)
{
	if(n < 0)
		return -n;
	
	return n;
}

void (*atexit_func)();
int atexit(void (*func)(void))
{
	atexit_func = func;
	return 0;
}

unsigned long int strtoul(const char* str, char** endptr, int base)
{
	// return __builtin_strtoul(str, endptr, base);
}

void* bsearch (const void* key, const void* base,
               size_t num, size_t size,
               int (*compar)(const void*,const void*))
{
	return NULL;
}

void qsort (void* base, size_t num, size_t size,
            int (*compar)(const void*,const void*))
{
	
}
