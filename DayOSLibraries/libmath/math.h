#ifndef __MATH_H
#define __MATH_H

/// FIXME: WRONG! WRONG! WRONG!
#define rint(x) ((int) (x))
#define HUGE_VAL (__builtin_huge_val())

#ifdef __cplusplus
extern "C" {
#endif

double floor(double x);
double fmod(double x, double y);
double pow(double b, double e);
double sin(double x);
double cos(double x);
double tan(double x);

double asin(double x);
double acos(double x);
double atan2(double x, double y);
double ceil(double x);
double sqrt(double x);
double log(double x);
double log10(double x);
double exp(double x);
double ldexp(double x, int exp);

double frexp(double x, int* exp);

double atan(double x);
double cosh(double x);
double fabs(double x);

double modf (double x, double* intpart);

double sinh(double x);
double tanh(double x);

#ifdef __cplusplus
}
#endif

#endif