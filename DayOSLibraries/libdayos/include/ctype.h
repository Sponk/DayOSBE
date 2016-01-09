#ifndef CTYPE_H
#define CTYPE_H

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