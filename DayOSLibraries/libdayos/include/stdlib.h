#ifndef STDLIB_H
#define STDLIB_H

#include <stddef.h>
#include <malloc.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE -1

#define RAND_MAX INT_MAX

typedef struct
{
	int quot;
	int rem;
} div_t;

typedef struct
{
	long int quot;
	long int rem;
} ldiv_t;

#ifdef __cplusplus
extern "C" {
#endif

void exit(int status);
int rand();
void srand(unsigned int seed);

long int strtol(const char* str, char** endptr, int base);
double strtod(const char* str, char** endptr);
void abort();

char* getenv(const char* name);
int system(const char* command);

div_t div (int numer, int denom);
ldiv_t ldiv(long int numer, long int denom);

long labs(long n);
int abs(int n);
int atexit(void (*func)(void));
float atof(const char* str);
int atoi(const char* str);
long atol(const char* str);
unsigned long int strtoul(const char* str, char** endptr, int base);

void* bsearch (const void* key, const void* base,
               size_t num, size_t size,
               int (*compar)(const void*,const void*));

void qsort (void* base, size_t num, size_t size,
            int (*compar)(const void*,const void*));

#ifdef __cplusplus
}
#endif

#endif
