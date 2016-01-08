#ifndef __LIMITS_H
#define __LIMITS_H

#ifdef __i386__

#define CHAR_BIT 8
#define SCHAR_MIN (-128)
#define SCHAR_MAX 127
#define CHAR_MIN SCHAR_MIN
#define CHAR_MAX SCHAR_MAX
#define UCHAR_MAX 255

#define INT_MIN 0//(−2147483648)
#define INT_MAX 2147483647

#define UINT_MAX 4294967295

#define LONG_MIN INT_MIN // Because of IA32
#define LONG_MAX INT_MAX // Because of IA32
#define ULONG_MAX UINT_MAX // Because of IA32

#define SHRT_MIN 0//(−32768)
#define SHRT_MAX 32767
#define USHRT_MAX 65535

#define MB_LEN_MAX 4

#define UINTPTR_MAX UINT_MAX
#define PATH_MAX 256

#define INTMAX_MIN 0
#define INTMAX_MAX 0
#define UINTMAX_MAX 2e64

#define UINT32_C unsigned int

#endif

#endif // __LIMITS_H