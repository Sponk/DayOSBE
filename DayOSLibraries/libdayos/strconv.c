#include <stdlib.h>

#define INLINE static
#include <ctype.h>

long int strtol(const char* str, char** endptr, int base)
{
	
}

double strtod(const char* str, char** endptr)
{
	
}

int atoi(const char* str)
{
	int value = 0;
	int is_negative = 1;
	
	// Skip all leading whitespace
	while(*str && isspace(*str)) str++;
	
	if(*str == '-') 
	{
		is_negative = -1;
		str++;
	}
	else if(*str == '+')
	{
		str++;
	}
	
	while(*str && isdigit(*str))
	{
		value *= 10;
		value += *str - '0';
		str++;
	}
	
	return value * is_negative;
}

float atof(const char* str)
{
	//return __builtin_atof(str);
}

long atol(const char* str)
{
	//return __builtin_atol(str);
}
