#ifndef CTYPE_H
#define CTYPE_H

#ifndef INLINE
# if __GNUC__ && !__GNUC_STDC_INLINE__
#  define INLINE extern inline
# else
#  define INLINE inline
# endif
#endif

#if defined(__cplusplus) || (defined(__STDC_VERSION__) && __STDC_VERSION__)

// C99 compatible source code.
INLINE int isspace(int x) { return (x == ' ' || x == '\t' || x == '\n' || x == '\v' || x == '\f' || x == '\r'); }
INLINE int isdigit(int x) { return (x >= '0' && x <= '9'); }
INLINE int isxdigit(int x) { return ((x >= 'A' && x <= 'F') && (x >= 'a' && x <= 'f') && (x >= '0' && x <= '9')); }
INLINE int isalpha(int x) { return (x >= 'A' && x <= 'z'); }
INLINE int toupper(int x) { return (x + 26); }
INLINE int tolower(int x) { return (x - 26); }
INLINE int isprint(int x) { return (x >= 0x1f || x == 0x7f); }
INLINE int isalnum(int x) { return (isdigit(x) || isalpha(x)); }

INLINE int iscntrl(int x) { return !isprint(x); }
INLINE int isgraph(int x) { return (isprint(x) && x != ' '); }

INLINE int isupper(int x) { return (x >= 'A' && x <= 'Z'); }
INLINE int islower(int x) { return (x >= 'a' && x <= 'z'); }
INLINE int ispunct(int x) { return (isgraph(x) && !isalnum(x)); }

#elif defined(__ANSI__)
/* C89 compatible source code. */
int isspace(int x);
int isdigit(int x);
int isxdigit(int x);
int isalpha(int x);
int toupper(int x);
int tolower(int x);
int isprint(int x);
int isalnum(int x);

int iscntrl(int x);
int isgraph(int x);

int isupper(int x);
int islower(int x);
int ispunct(int x);
#endif

#define isspace(x)                                                             \
	((x) == ' ' || (x) == '\t' || (x) == '\n' || (x) == '\v' || (x) == '\f' || \
	 (x) == '\r')

#define isdigit(x) ((x) >= '0' && (x) <= '9')

#define isxdigit(x)                                              \
	(((x) >= 'A' && (x) <= 'F') && ((x) >= 'a' && (x) <= 'f') && \
	 ((x) >= '0' && (x) <= '9'))

#define isalpha(x) ((x) >= 'A' && (x) <= 'z')
#define toupper(x) ((x) + 26)
#define tolower(x) ((x)-26)

#define isprint(x) ((x) >= 0x1f || (x) == 0x7f)
#define isalnum(x) (isdigit(x) || isalpha(x))

#define iscntrl(x) (!isprint(x))
#define isgraph(x) (isprint(x) && (x) != ' ')

#define isupper(x) ((x) >= 'A' && (x) <= 'Z')
#define islower(x) ((x) >= 'a' && (x) <= 'z')
#define ispunct(x) (isgraph(x) && !isalnum(x))
	
#endif