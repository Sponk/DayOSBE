#include "math.h"

double floor(double x)
{
	return __builtin_floor(x);
}

double fmod(double x, double y)
{
	return __builtin_fmod(x,y);
}

double pow(double b, double e)
{
	return __builtin_pow(b, e);
}

double sin(double x)
{
	return __builtin_sin(x);
}

double cos(double x)
{
	return __builtin_cos(x);
}

double tan(double x)
{
	return __builtin_tan(x);
}

double asin(double x)
{
	return __builtin_asin(x);
}

double acos(double x)
{
	return __builtin_acos(x);
}

double atan2(double x, double y)
{
	return __builtin_atan2(x, y);
}

double sqrt(double x)
{
	return __builtin_sqrt(x);
}

double log(double x)
{
	return __builtin_log(x);
}

double log10(double x)
{
	return __builtin_log10(x);
}

double exp(double x)
{
	return __builtin_exp(x);
}

double ldexp(double x, int exp)
{
	return __builtin_ldexp(x, exp);
}

double ceil(double x)
{
	return __builtin_ceil(x);
}

double frexp(double x, int* exp)
{
	return __builtin_frexp(x, exp);
}

long long __udivdi3(long long a, long long b)
{
	return 0;
	//return __builtin_udivdi3(a, b);
}

double atan(double x)
{
	return __builtin_atan(x);
}

double cosh(double x)
{
	return __builtin_cosh(x);
}

double fabs(double x)
{
	return __builtin_fabs(x);
}

double modf(double x, double* intpart)
{
	return __builtin_modf(x, intpart);
}

double sinh(double x)
{
	return __builtin_sinh(x);
}

double tanh(double x)
{
	return __builtin_tanh(x);
}

double trunc(double x)
{
	return __builtin_trunc(x);
}

float truncf(float x)
{
	return __builtin_truncf(x);
}
